/*
  decode_imap.c

  Internet Mail Access Protocol.
  
  Copyright (c) 2000 Dug Song <dugsong@monkey.org>
  
  $Id: decode_imap.c,v 1.2 2005-07-08 13:36:59 cmn Exp $
*/

#ifndef NO_PASSWD_SCAN

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "buf.h"

int
decode_imap(u_char *buf, int len, u_char *obuf, int olen)
{
	struct buf *line, inbuf, outbuf;
	int i;

	buf_init(&inbuf, buf, len);
	buf_init(&outbuf, obuf, olen);
	
	while ((i = buf_index(&inbuf, "\r\n", 2)) != -1) {
		line = buf_tok(&inbuf, NULL, i);
		buf_skip(&inbuf, 2);

		if ((i = buf_index(line, " ", 1)) != -1) {
			buf_skip(line, i + 1);
		
			if (buf_cmp(line, "LOGIN ", 6) == 0) {
				buf_putf(&outbuf, "%.*s\n",
					 buf_len(line), buf_ptr(line));
			}
		}
	}
	buf_end(&outbuf);
	
	return (buf_len(&outbuf));
}

#endif /* NO_PASSWD_SCAN */
