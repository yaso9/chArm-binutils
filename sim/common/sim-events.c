/*  This file is part of the program psim.

    Copyright (C) 1994-1997, Andrew Cagney <cagney@highland.com.au>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
    */


#ifndef _SIM_EVENTS_C_
#define _SIM_EVENTS_C_

#include "sim-main.h"
#include "sim-assert.h"

#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

#include <signal.h>


typedef enum {
  watch_invalid,

  /* core - target byte order */
  watch_core_targ_1,
  watch_core_targ_2,
  watch_core_targ_4,
  watch_core_targ_8,
  /* core - big-endian */
  watch_core_be_1,
  watch_core_be_2,
  watch_core_be_4,
  watch_core_be_8,
  /* core - little-endian */
  watch_core_le_1,
  watch_core_le_2,
  watch_core_le_4,
  watch_core_le_8,

  /* sim - host byte order */
  watch_sim_host_1,
  watch_sim_host_2,
  watch_sim_host_4,
  watch_sim_host_8,
  /* sim - big-endian */
  watch_sim_be_1,
  watch_sim_be_2,
  watch_sim_be_4,
  watch_sim_be_8,
  /* sim - little-endian */
  watch_sim_le_1,
  watch_sim_le_2,
  watch_sim_le_4,
  watch_sim_le_8,
  
  /* wallclock */
  watch_clock,

  /* timer */
  watch_timer,
} sim_event_watchpoints;


struct _sim_event {
  sim_event_watchpoints watching;
  void *data;
  sim_event_handler *handler;
  /* timer event */
  signed64 time_of_event;
  /* watch wallclock event */
  unsigned wallclock;
  /* watch core address */
  address_word core_addr;
  sim_core_maps core_map;
  /* watch sim addr */
  void *host_addr;
  /* watch core/sim range */
  int is_within; /* 0/1 */
  unsigned ub;
  unsigned lb;
  unsigned64 ub64;
  unsigned64 lb64;
  /* list */
  sim_event *next;
};


/* The event queue maintains a single absolute time using two
   variables.
   
   TIME_OF_EVENT: this holds the time at which the next event is ment
   to occure.  If no next event it will hold the time of the last
   event.

   TIME_FROM_EVENT: The current distance from TIME_OF_EVENT.  If an
   event is pending, this will be positive.  If no future event is
   pending (eg when poll-event is being processed) this will be
   negative.  This variable is decremented once for each iteration of
   a clock cycle.

   Initially, the clock is started at time one (0) with TIME_OF_EVENT
   == 0 and TIME_FROM_EVENT == 0.

   Clearly there is a bug in that this code assumes that the absolute
   time counter will never become greater than 2^62.

   To avoid the need to use 64bit arithmetic, the event queue always
   contains at least one event scheduled every 16 000 ticks.  This
   limits the time from event counter to values less than
   16 000. */


#if !defined (SIM_EVENTS_POLL_RATE)
#define SIM_EVENTS_POLL_RATE 0x100000
#endif


#define _ETRACE sd

#undef ETRACE
#define ETRACE(ARGS) \
do \
  { \
    if (WITH_TRACE) \
      { \
        if (STATE_EVENTS (sd)->trace) \
          { \
            const char *file; \
            SIM_FILTER_PATH (file, __FILE__); \
            sim_io_printf (sd, "%s:%d: ", file, __LINE__); \
            sim_io_printf  ARGS; \
          } \
      } \
  } \
while (0)


/* event queue iterator - don't iterate over the held queue. */

STATIC_INLINE_SIM_EVENTS\
(sim_event **)
next_event_queue (SIM_DESC sd,
		  sim_event **queue)
{
  if (queue == NULL)
    return &STATE_EVENTS (sd)->queue;
  else if (queue == &STATE_EVENTS (sd)->queue)
    return &STATE_EVENTS (sd)->watchpoints;
  else if (queue == &STATE_EVENTS (sd)->watchpoints)
    return &STATE_EVENTS (sd)->watchedpoints;
  else if (queue == &STATE_EVENTS (sd)->watchedpoints)
    return NULL;
  else
    sim_io_error (sd, "next_event_queue - bad queue");
  return NULL;
}


STATIC_INLINE_SIM_EVENTS\
(void)
sim_events_poll (SIM_DESC sd,
		 void *data)
{
  /* just re-schedule in 1000 million ticks time */
  sim_events_schedule (sd, SIM_EVENTS_POLL_RATE, sim_events_poll, sd);
  sim_io_poll_quit (sd);
}


/* "events" module install handler.
   This is called via sim_module_install to install the "events" subsystem
   into the simulator.  */

EXTERN_SIM_EVENTS\
(SIM_RC)
sim_events_install (SIM_DESC sd)
{
  SIM_ASSERT (STATE_MAGIC (sd) == SIM_MAGIC_NUMBER);
  sim_module_add_uninstall_fn (sd, sim_events_uninstall);
  sim_module_add_init_fn (sd, sim_events_init);
  return SIM_RC_OK;
}


/* Uninstall the "events" subsystem from the simulator.  */

EXTERN_SIM_EVENTS\
(void)
sim_events_uninstall (SIM_DESC sd)
{
  /* FIXME: free buffers, etc. */
}


/* malloc/free */

STATIC_INLINE_SIM_EVENTS\
(sim_event *)
sim_events_zalloc (SIM_DESC sd)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *new = events->free_list;
  if (new != NULL)
    {
      events->free_list = new->next;
      memset (new, 0, sizeof (*new));
    }
  else
    {
#if defined (HAVE_SIGPROCMASK) && defined (SIG_SETMASK)
      /*-LOCK-*/
      sigset_t old_mask;
      sigset_t new_mask;
      sigfillset(&new_mask);
      sigprocmask (SIG_SETMASK, &new_mask, &old_mask);
#endif
      new = ZALLOC (sim_event);
#if defined (HAVE_SIGPROCMASK) && defined (SIG_SETMASK)
      /*-UNLOCK-*/
      sigprocmask (SIG_SETMASK, &old_mask, NULL);
#endif
    }
  return new;
}

STATIC_INLINE_SIM_EVENTS\
(void)
sim_events_free (SIM_DESC sd,
		 sim_event *dead)
{
  sim_events *events = STATE_EVENTS (sd);
  dead->next = events->free_list;
  events->free_list = dead;
}


/* Initialize the simulator event manager */

EXTERN_SIM_EVENTS\
(SIM_RC)
sim_events_init (SIM_DESC sd)
{
  sim_events *events = STATE_EVENTS (sd);

  /* drain the interrupt queue */
  events->nr_held = 0;
  if (events->held == NULL)
    events->held = zalloc (sizeof (sim_event) * MAX_NR_SIGNAL_SIM_EVENTS);

  /* drain the normal queues */
  {
    sim_event **queue = NULL;
    while ((queue = next_event_queue (sd, queue)) != NULL)
      {
	if (queue == NULL) break;
	while (*queue != NULL)
	  {
	    sim_event *dead = *queue;
	    *queue = dead->next;
	    sim_events_free (sd, dead);
	  }
	*queue = NULL;
      }
  }

  /* wind time back to zero */
  events->nr_ticks_to_process = 1; /* start by doing queue */
  events->time_of_event = 0;
  events->time_from_event = 0;
  events->initial_wallclock = sim_elapsed_time_get ();

  /* schedule our initial counter event */
  sim_events_schedule (sd, 0, sim_events_poll, sd);

  /* from now on, except when the large-int event is being processed
     the event queue is non empty */
  SIM_ASSERT (events->queue != NULL);

  return SIM_RC_OK;
}


INLINE_SIM_EVENTS\
(signed64)
sim_events_time (SIM_DESC sd)
{
  sim_events *events = STATE_EVENTS (sd);
  return events->time_of_event - events->time_from_event;
}


STATIC_INLINE_SIM_EVENTS\
(void)
update_time_from_event (SIM_DESC sd)
{
  sim_events *events = STATE_EVENTS (sd);
  signed64 current_time = sim_events_time (sd);
  if (events->queue != NULL)
    {
      events->time_from_event = (events->queue->time_of_event - current_time);
      events->time_of_event = events->queue->time_of_event;
    }
  else
    {
      events->time_of_event = current_time - 1;
      events->time_from_event = -1;
    }
  SIM_ASSERT (current_time == sim_events_time (sd));
  SIM_ASSERT ((events->time_from_event >= 0) == (events->queue != NULL));
}


STATIC_INLINE_SIM_EVENTS\
(void)
insert_sim_event (SIM_DESC sd,
		  sim_event *new_event,
		  signed64 delta)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *curr;
  sim_event **prev;
  signed64 time_of_event;

  if (delta < 0)
    sim_io_error (sd, "what is past is past!\n");
  
  /* compute when the event should occure */
  time_of_event = sim_events_time (sd) + delta;
  
  /* find the queue insertion point - things are time ordered */
  prev = &events->queue;
  curr = events->queue;
  while (curr != NULL && time_of_event >= curr->time_of_event)
    {
      SIM_ASSERT (curr->next == NULL
		  || curr->time_of_event <= curr->next->time_of_event);
      prev = &curr->next;
      curr = curr->next;
    }
  SIM_ASSERT (curr == NULL || time_of_event < curr->time_of_event);
  
  /* insert it */
  new_event->next = curr;
  *prev = new_event;
  new_event->time_of_event = time_of_event;
  
  /* adjust the time until the first event */
  update_time_from_event (sd);
}


EXTERN_SIM_EVENTS\
(sim_event *)
sim_events_schedule (SIM_DESC sd,
		     signed64 delta_time,
		     sim_event_handler *handler,
		     void *data)
{
  sim_event *new_event = sim_events_zalloc (sd);
  new_event->data = data;
  new_event->handler = handler;
  new_event->watching = watch_timer;
  insert_sim_event(sd, new_event, delta_time);
  ETRACE((_ETRACE,
	  "event scheduled at %ld - tag 0x%lx - time %ld, handler 0x%lx, data 0x%lx\n",
	  (long)sim_events_time(sd),
	  (long)new_event,
	  (long)new_event->time_of_event,
	  (long)new_event->handler,
	  (long)new_event->data));
  return new_event;
}


EXTERN_SIM_EVENTS\
(void)
sim_events_schedule_after_signal (SIM_DESC sd,
				  signed64 delta_time,
				  sim_event_handler *handler,
				  void *data)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *new_event;
#if defined (HAVE_SIGPROCMASK) && defined (SIG_SETMASK)
  /*-LOCK-*/
  sigset_t old_mask;
  sigset_t new_mask;
  sigfillset(&new_mask);
  sigprocmask (SIG_SETMASK, &new_mask, &old_mask);
#endif
  
  /* allocate an event entry from the signal buffer */
  new_event = &events->held [events->nr_held];
  events->nr_held ++;
  if (events->nr_held >= MAX_NR_SIGNAL_SIM_EVENTS)
    {
      sim_engine_abort (NULL, NULL, NULL_CIA,
			"sim_events_schedule_after_signal - buffer oveflow");
    }
  
  new_event->data = data;
  new_event->handler = handler;
  new_event->time_of_event = delta_time; /* work it out later */
  new_event->next = NULL;

  events->work_pending = 1; /* notify main process */

#if defined (HAVE_SIGPROCMASK) && defined (SIG_SETMASK)
  /*-UNLOCK-*/
  sigprocmask (SIG_SETMASK, &old_mask, NULL);
#endif
  
  ETRACE ((_ETRACE,
	   "signal scheduled at %ld - tag 0x%lx - time %ld, handler 0x%lx, data 0x%lx\n",
	   (long)sim_events_time(sd),
	   (long)new_event,
	   (long)new_event->time_of_event,
	   (long)new_event->handler,
	   (long)new_event->data));
}


EXTERN_SIM_EVENTS\
(sim_event *)
sim_events_watch_clock (SIM_DESC sd,
			unsigned delta_ms_time,
			sim_event_handler *handler,
			void *data)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *new_event = sim_events_zalloc (sd);
  /* type */
  new_event->watching = watch_clock;
  /* handler */
  new_event->data = data;
  new_event->handler = handler;
  /* data */
  new_event->wallclock = (sim_elapsed_time_since (events->initial_wallclock) + delta_ms_time);
  /* insert */
  new_event->next = events->watchpoints;
  events->watchpoints = new_event;
  events->work_pending = 1;
  ETRACE ((_ETRACE,
	  "event watching clock at %ld - tag 0x%lx - wallclock %ld, handler 0x%lx, data 0x%lx\n",
	   (long)sim_events_time (sd),
	   (long)new_event,
	   (long)new_event->wallclock,
	   (long)new_event->handler,
	   (long)new_event->data));
  return new_event;
}


EXTERN_SIM_EVENTS\
(sim_event *)
sim_events_watch_sim (SIM_DESC sd,
		      void *host_addr,
		      int nr_bytes,
		      int byte_order,
		      int is_within,
		      unsigned64 lb,
		      unsigned64 ub,
		      sim_event_handler *handler,
		      void *data)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *new_event = sim_events_zalloc (sd);
  /* type */
  switch (byte_order)
    {
    case 0:
      switch (nr_bytes)
	{
	case 1: new_event->watching = watch_sim_host_1; break;
	case 2: new_event->watching = watch_sim_host_2; break;
	case 4: new_event->watching = watch_sim_host_4; break;
	case 8: new_event->watching = watch_sim_host_8; break;
	default: sim_io_error (sd, "sim_events_watch_sim - invalid nr bytes");
	}
      break;
    case BIG_ENDIAN:
      switch (nr_bytes)
	{
	case 1: new_event->watching = watch_sim_be_1; break;
	case 2: new_event->watching = watch_sim_be_2; break;
	case 4: new_event->watching = watch_sim_be_4; break;
	case 8: new_event->watching = watch_sim_be_8; break;
	default: sim_io_error (sd, "sim_events_watch_sim - invalid nr bytes");
	}
      break;
    case LITTLE_ENDIAN:
      switch (nr_bytes)
	{
	case 1: new_event->watching = watch_sim_le_1; break;
	case 2: new_event->watching = watch_sim_le_2; break;
	case 4: new_event->watching = watch_sim_le_4; break;
	case 8: new_event->watching = watch_sim_le_8; break;
	default: sim_io_error (sd, "sim_events_watch_sim - invalid nr bytes");
	}
      break;
    default:
      sim_io_error (sd, "sim_events_watch_sim - invalid byte order");
    }
  /* handler */
  new_event->data = data;
  new_event->handler = handler;
  /* data */
  new_event->host_addr = host_addr;
  new_event->lb = lb;
  new_event->lb64 = lb;
  new_event->ub = ub;
  new_event->ub64 = ub;
  new_event->is_within = (is_within != 0);
  /* insert */
  new_event->next = events->watchpoints;
  events->watchpoints = new_event;
  events->work_pending = 1;
  ETRACE ((_ETRACE,
	   "event watching host at %ld - tag 0x%lx - host-addr 0x%lx, 0x%lx..0x%lx, handler 0x%lx, data 0x%lx\n",
	   (long)sim_events_time (sd),
	   (long)new_event,
	   (long)new_event->host_addr,
	   (long)new_event->lb,
	   (long)new_event->ub,
	   (long)new_event->handler,
	   (long)new_event->data));
  return new_event;
}


EXTERN_SIM_EVENTS\
(sim_event *)
sim_events_watch_core (SIM_DESC sd,
		       address_word core_addr,
		       sim_core_maps core_map,
		       int nr_bytes,
		       int byte_order,
		       int is_within,
		       unsigned64 lb,
		       unsigned64 ub,
		       sim_event_handler *handler,
		       void *data)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *new_event = sim_events_zalloc (sd);
  /* type */
  switch (byte_order)
    {
    case 0:
      switch (nr_bytes)
	{
	case 1: new_event->watching = watch_core_targ_1; break;
	case 2: new_event->watching = watch_core_targ_2; break;
	case 4: new_event->watching = watch_core_targ_4; break;
	case 8: new_event->watching = watch_core_targ_8; break;
	default: sim_io_error (sd, "sim_events_watch_core - invalid nr bytes");
	}
      break;
    case BIG_ENDIAN:
      switch (nr_bytes)
	{
	case 1: new_event->watching = watch_core_be_1; break;
	case 2: new_event->watching = watch_core_be_2; break;
	case 4: new_event->watching = watch_core_be_4; break;
	case 8: new_event->watching = watch_core_be_8; break;
	default: sim_io_error (sd, "sim_events_watch_core - invalid nr bytes");
	}
      break;
    case LITTLE_ENDIAN:
      switch (nr_bytes)
	{
	case 1: new_event->watching = watch_core_le_1; break;
	case 2: new_event->watching = watch_core_le_2; break;
	case 4: new_event->watching = watch_core_le_4; break;
	case 8: new_event->watching = watch_core_le_8; break;
	default: sim_io_error (sd, "sim_events_watch_core - invalid nr bytes");
	}
      break;
    default:
      sim_io_error (sd, "sim_events_watch_core - invalid byte order");
    }
  /* handler */
  new_event->data = data;
  new_event->handler = handler;
  /* data */
  new_event->core_addr = core_addr;
  new_event->core_map = core_map;
  new_event->lb = lb;
  new_event->lb64 = lb;
  new_event->ub = ub;
  new_event->ub64 = ub;
  new_event->is_within = (is_within != 0);
  /* insert */
  new_event->next = events->watchpoints;
  events->watchpoints = new_event;
  events->work_pending = 1;
  ETRACE ((_ETRACE,
	   "event watching host at %ld - tag 0x%lx - host-addr 0x%lx, 0x%lx..0x%lx, handler 0x%lx, data 0x%lx\n",
	   (long)sim_events_time (sd),
	   (long)new_event,
	   (long)new_event->host_addr,
	   (long)new_event->lb,
	   (long)new_event->ub,
	   (long)new_event->handler,
	   (long)new_event->data));
  return new_event;
}


EXTERN_SIM_EVENTS\
(void)
sim_events_deschedule (SIM_DESC sd,
		       sim_event *event_to_remove)
{
  sim_events *events = STATE_EVENTS (sd);
  sim_event *to_remove = (sim_event*)event_to_remove;
  SIM_ASSERT ((events->time_from_event >= 0) == (events->queue != NULL));
  if (event_to_remove != NULL)
    {
      sim_event **queue = NULL;
      while ((queue = next_event_queue (sd, queue)) != NULL)
	{
	  sim_event **ptr_to_current;
	  for (ptr_to_current = queue;
	       *ptr_to_current != NULL && *ptr_to_current != to_remove;
	       ptr_to_current = &(*ptr_to_current)->next);
	  if (*ptr_to_current == to_remove)
	    {
	      sim_event *dead = *ptr_to_current;
	      *ptr_to_current = dead->next;
	      ETRACE ((_ETRACE,
		       "event/watch descheduled at %ld - tag 0x%lx - time %ld, handler 0x%lx, data 0x%lx\n",
		       (long) sim_events_time (sd),
		       (long) event_to_remove,
		       (long) dead->time_of_event,
		       (long) dead->handler,
		       (long) dead->data));
	      sim_events_free (sd, dead);
	      update_time_from_event (sd);
	      SIM_ASSERT ((events->time_from_event >= 0) == (events->queue != NULL));
	      return;
	    }
	}
    }
  ETRACE ((_ETRACE,
	   "event/watch descheduled at %ld - tag 0x%lx - not found\n",
	   (long) sim_events_time (sd),
	   (long) event_to_remove));
}


STATIC_INLINE_SIM_EVENTS\
(int)
sim_watch_valid (SIM_DESC sd,
		 sim_event *to_do)
{
  switch (to_do->watching)
    {

#define WATCH_CORE(N,OP,EXT) \
      { \
	unsigned_##N word = 0; \
	int nr_read = sim_core_read_buffer (sd, NULL, to_do->core_map, &word, to_do->core_addr, sizeof (word)); \
	OP (word); \
	return (nr_read == sizeof (unsigned_##N) \
		&& (to_do->is_within \
		    == (word >= to_do->lb##EXT \
			&& word <= to_do->ub##EXT))); \
      }
    case watch_core_targ_1: WATCH_CORE (1, T2H,);
    case watch_core_targ_2: WATCH_CORE (2, T2H,);
    case watch_core_targ_4: WATCH_CORE (4, T2H,);
    case watch_core_targ_8: WATCH_CORE (8, T2H,64);

    case watch_core_be_1: WATCH_CORE (1, BE2H,);
    case watch_core_be_2: WATCH_CORE (2, BE2H,);
    case watch_core_be_4: WATCH_CORE (4, BE2H,);
    case watch_core_be_8: WATCH_CORE (8, BE2H,64);

    case watch_core_le_1: WATCH_CORE (1, LE2H,);
    case watch_core_le_2: WATCH_CORE (2, LE2H,);
    case watch_core_le_4: WATCH_CORE (4, LE2H,);
    case watch_core_le_8: WATCH_CORE (8, LE2H,64);
#undef WATCH_CORE

#define WATCH_SIM(N,OP,EXT) \
      { \
	unsigned_##N word = *(unsigned_##N*)to_do->host_addr; \
        OP (word); \
	return (to_do->is_within \
		== (word >= to_do->lb##EXT \
		    && word <= to_do->ub##EXT)); \
      }

    case watch_sim_host_1: WATCH_SIM (1, word = ,);
    case watch_sim_host_2: WATCH_SIM (2, word = ,);
    case watch_sim_host_4: WATCH_SIM (4, word = ,);
    case watch_sim_host_8: WATCH_SIM (8, word = ,64);

    case watch_sim_be_1: WATCH_SIM (1, BE2H,);
    case watch_sim_be_2: WATCH_SIM (2, BE2H,);
    case watch_sim_be_4: WATCH_SIM (4, BE2H,);
    case watch_sim_be_8: WATCH_SIM (8, BE2H,64);

    case watch_sim_le_1: WATCH_SIM (1, LE2H,);
    case watch_sim_le_2: WATCH_SIM (1, LE2H,);
    case watch_sim_le_4: WATCH_SIM (1, LE2H,);
    case watch_sim_le_8: WATCH_SIM (1, LE2H,64);
#undef WATCH_SIM

    case watch_clock: /* wallclock */
      {
	unsigned long elapsed_time = sim_elapsed_time_since (STATE_EVENTS (sd)->initial_wallclock);
	return (elapsed_time >= to_do->wallclock);
      }

    default:
      sim_io_error (sd, "sim_watch_valid - bad switch");
      break;

    }
  return 1;
}


INLINE_SIM_EVENTS\
(int)
sim_events_tick (SIM_DESC sd)
{
  sim_events *events = STATE_EVENTS (sd);

  /* this should only be called after the previous ticks have been
     fully processed */
  SIM_ASSERT (events->nr_ticks_to_process == 0);

  /* Advance the time but *only* if there is nothing to process */
  if (events->work_pending
      || events->time_from_event == 0)
    {
      events->nr_ticks_to_process = 1;
      return 1;
    }
  else {
    events->time_from_event -= 1;
    return 0;
  }
}


INLINE_SIM_EVENTS\
(int)
sim_events_tickn (SIM_DESC sd,
		  unsigned n)
{
  sim_events *events = STATE_EVENTS (sd);

  /* this should only be called after the previous ticks have been
     fully processed */
  SIM_ASSERT (events->nr_ticks_to_process == 0);
  SIM_ASSERT (n > 0);

  /* Advance the time but *only* if there is nothing to process */
  if (events->work_pending
      || events->time_from_event < n)
    {
      events->nr_ticks_to_process = n;
      return 1;
    }
  else {
    events->time_from_event -= n;
    return 0;
  }
}


INLINE_SIM_EVENTS\
(void)
sim_events_preprocess (SIM_DESC sd,
		       int events_were_last,
		       int events_were_next)
{
  sim_events *events = STATE_EVENTS(sd);
  if (events->nr_ticks_to_process != 0)
    {
      /* Halted midway through event processing */
      ASSERT (events_were_last && events_were_next);
      sim_events_process (sd);
    }
  else if (events_were_next)
    {
      /* Halted by the last processor */
      ASSERT (events->nr_ticks_to_process == 0 && !events_were_last);
      if (sim_events_tick (sd))
	sim_events_process (sd);
    }
}


INLINE_SIM_EVENTS\
(void)
sim_events_process (SIM_DESC sd)
{
  sim_events *events = STATE_EVENTS(sd);
  signed64 event_time = sim_events_time(sd);

  ASSERT (events->nr_ticks_to_process != 0);

  /* move any events that were queued by any signal handlers onto
     the real event queue.  */
  if (events->nr_held > 0)
    {
      int i;
      
#if defined(HAVE_SIGPROCMASK) && defined(SIG_SETMASK)
      /*-LOCK-*/
      sigset_t old_mask;
      sigset_t new_mask;
      sigfillset(&new_mask);
      sigprocmask(SIG_SETMASK, &new_mask, &old_mask);
#endif
      
      for (i = 0; i < events->nr_held; i++)
	{
	  sim_event *entry = &events->held [i];
	  sim_events_schedule (sd,
			       entry->time_of_event,
			       entry->handler,
			       entry->data);
	}
      events->nr_held = 0;
      
#if defined(HAVE_SIGPROCMASK) && defined(SIG_SETMASK)
      /*-UNLOCK-*/
      sigprocmask(SIG_SETMASK, &old_mask, NULL);
#endif
      
    }
  
  /* Process any watchpoints. Be careful to allow a watchpoint to
     appear/disappear under our feet.
     To ensure that watchpoints are processed only once per cycle,
     they are moved onto a watched queue, this returned to the
     watchpoint queue when all queue processing has been
     completed. */
  while (events->watchpoints != NULL)
    {
      sim_event *to_do = events->watchpoints;
      events->watchpoints = to_do->next;
      if (sim_watch_valid (sd, to_do))
	{
	  sim_event_handler *handler = to_do->handler;
	  void *data = to_do->data;
	  events->queue = to_do->next;
	  ETRACE((_ETRACE,
		  "event issued at %ld - tag 0x%lx - handler 0x%lx, data 0x%lx\n",
		  (long) event_time,
		  (long) to_do,
		  (long) handler,
		  (long) data));
	  sim_events_free (sd, to_do);
	  handler (sd, data);
	}
      else
	{
	  to_do->next = events->watchedpoints;
	  events->watchedpoints = to_do;
	}
    }
  
  /* consume all events for this or earlier times.  Be careful to
     allow an event to appear/disappear under our feet */
  while (events->queue->time_of_event <
	 (event_time + events->nr_ticks_to_process))
    {
      sim_event *to_do = events->queue;
      sim_event_handler *handler = to_do->handler;
      void *data = to_do->data;
      events->queue = to_do->next;
      ETRACE((_ETRACE,
	      "event issued at %ld - tag 0x%lx - handler 0x%lx, data 0x%lx\n",
	      (long) event_time,
	      (long) to_do,
	      (long) handler,
	      (long) data));
      sim_events_free (sd, to_do);
      handler (sd, data);
    }
  
  /* put things back where they belong ready for the next iteration */
  events->watchpoints = events->watchedpoints;
  events->watchedpoints = NULL;
  if (events->watchpoints != NULL)
    events->work_pending = 1;
  
  /* re-caculate time for new events then advance the time */
  update_time_from_event(sd);
  SIM_ASSERT (events->time_from_event >= events->nr_ticks_to_process);
  SIM_ASSERT (events->queue != NULL); /* always poll event */
  events->time_from_event -= events->nr_ticks_to_process;

  /* this round of processing complete */
  events->nr_ticks_to_process = 0;
}

#endif
