/*
 * $Id$
 *
 * Copyright (C) 2012 Crocodile RCS Ltd
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef _WS_CONN_H
#define _WS_CONN_H

#include "../../locking.h"
#include "../../lib/kmi/tree.h"

typedef enum
{
	WS_S_CONNECTING	= 0,	/* Never used - included for completeness */
	WS_S_OPEN,
	WS_S_CLOSING,
	WS_S_CLOSED		/* Never used - included for completeness */
} ws_conn_state_t;

typedef struct ws_connection
{
	ws_conn_state_t state;
	int last_used;

	int id;			/* id and id_hash are identical to the values */
	unsigned id_hash;	/* for the corresponding TCP/TLS connection */
	struct ws_connection *id_prev;
	struct ws_connection *id_next;
} ws_connection_t;

#define wsconn_listadd	tcpconn_listadd
#define wsconn_listrm	tcpconn_listrm

extern char *wsconn_state_str[];

extern stat_var *ws_current_connections;
extern stat_var *ws_max_concurrent_connections;

int wsconn_init(void);
void wsconn_destroy(void);
int wsconn_add(int id);
int wsconn_rm(ws_connection_t *wsc);
int wsconn_update(ws_connection_t *wsc);
void wsconn_close_now(ws_connection_t *wsc);
ws_connection_t *wsconn_get(int id);
struct mi_root *ws_mi_dump(struct mi_root *cmd, void *param);

#endif /* _WS_CONN_H */