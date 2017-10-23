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
 * $Id: dcap_url.h,v 1.5 2004-11-01 19:33:29 tigran Exp $
 */
#ifndef DCAP_URL_H
#define DCAP_URL_H

#define URL_NONE 0
#define URL_DCAP 1
#define URL_PNFS 2

typedef struct {
	char *host;
	char *file;
	int type;
	char *prefix;
        short port;
        int need_brackets;
} dcap_url;

extern dcap_url *dc_getURL(const char *);
extern int isUrl(const char *);
extern const char *get_url_string(dcap_url *url);
extern void free_url(dcap_url *url);

#endif /* DCAP_URL_H */
