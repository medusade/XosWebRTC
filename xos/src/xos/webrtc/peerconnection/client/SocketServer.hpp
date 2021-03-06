///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: SocketServer.hpp
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_WEBRTC_PEERCONNECTION_CLIENT_SOCKETSERVER_HPP
#define _XOS_WEBRTC_PEERCONNECTION_CLIENT_SOCKETSERVER_HPP

#include "xos/webrtc/peerconnection/talk/base/SocketServer.hpp"
#include "xos/webrtc/peerconnection/client/MainWindow.hpp"

namespace xos {
namespace webrtc {
namespace peerconnection {
namespace client {

typedef talk::base::physical::SocketServer SocketServerExtends;
///////////////////////////////////////////////////////////////////////
///  Class: SocketServer
///
/// Author: $author$
///   Date: 12/25/2012
///////////////////////////////////////////////////////////////////////
template <class TExtend = SocketServerExtends>

class _EXPORT_CLASS SocketServer: public TExtend {
public:
    typedef TExtend Extends;

    SocketServer(MainWindow& mainWindow):m_peerWindow(mainWindow) {
    }
    virtual ~SocketServer() {
    }
    virtual bool PeekQuitMessage(int& cms, bool& process_io) { 
        int msg_id, id;
        void* data;

        if ((PeekUIMessage(msg_id, id, data))) {
            switch(msg_id) {
            case MainWindow::UI_THREAD_QUIT:
                return true;
                break;
            case MainWindow::UI_THREAD_WAKEUP:
                break;
            default:
                m_peerWindow.OnUIMessage(msg_id, id, data);
            }
        }
        return false; 
    }
    virtual bool PeekUIMessage(int& msg_id, int& id, void*& data) {
        return m_peerWindow.PeekUIMessage(msg_id, id, data);
    }
protected:
    MainWindow& m_peerWindow;
};

namespace physical {

typedef client::SocketServer<talk::base::physical::SocketServer> SocketServer;

} // namespace physical

} // namespace client 
} // namespace peerconnection 
} // namespace webrtc 
} // namespace xos 

#endif // _XOS_WEBRTC_PEERCONNECTION_CLIENT_SOCKETSERVER_HPP 
