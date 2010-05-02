/* Copyright (c) 2010 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for any purpose
 * with or without fee is hereby granted, provided that the above copyright
 * notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <Common.h>
#include <Buffer.h>
#include <Service.h>
#include <TCPTransport.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * \file
 * A telnet client over TCPTransport.
 */

int
main()
{
    RAMCloud::Service service;
    service.setIp(inet_addr(SVRADDR));
    service.setPort(SVRPORT);
    RAMCloud::TCPTransport tx("127.0.0.1", 0);
    char buf[1024];
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        RAMCloud::Transport::ClientToken token;
        RAMCloud::Buffer request;
        RAMCloud::Buffer response;
        request.append(buf, static_cast<uint32_t>(strlen(buf)));
        tx.clientSend(&service, &request, &token);
        tx.clientRecv(&response, &token);
        void* contigResp = response.getRange(0, response.totalLength());
        puts(static_cast<char*>(contigResp));
    }
    return 0;
};