/*
 *   DCAP - dCache Access Protocol client interface
 *
 *   Copyright (C) 2000,2004 DESY Hamburg DMG-Division.
 *
 *   AUTHOR: Tigran Mkrtchayn (tigran.mkrtchyan@desy.de)
 *
 *   This program can be distributed under the terms of the GNU LGPL.
 *   See the file COPYING.LIB
 *
 */


/*
 * $Id: dcap_mkdir.c,v 1.4 2004-11-01 19:33:29 tigran Exp $
 */

#include <stdlib.h>
#include <string.h>

#include "dcap.h"
#include "dcap_protocol.h"
#include "dcap_functions.h"
#include "dcap_mqueue.h"
#include "dcap_url.h"
#include "node_plays.h"
#include "debug_level.h"
#include "system_io.h"


int dc_mkdir( const char *path, mode_t mode)
 {


	dcap_url *url;
	struct vsp_node *node;
	int rc;
	mode_t mask;


	url = (dcap_url *)dc_getURL(path);
 	if( url == NULL ) {
		dc_debug(DC_INFO, "Using system native mkdir for %s.", path);
		return system_mkdir(path, mode);

	}


 	node = new_vsp_node( path );
	if( node == NULL ) {
		free_url(url);
		return 1;
	}

	node->url = url;
	node->pnfsId = (char *)get_url_string(url);
	node->asciiCommand = DCAP_CMD_MKDIR;

	/* get the mask */
	mask = umask(0);
	umask(mask);

	node->mode = mode & ~mask;

	rc = cache_open(node);

	/* node cleanup procedure */
	node_unplug( node );

	deleteQueue(node->queueID);
	node_destroy(node);

	return rc;

}
