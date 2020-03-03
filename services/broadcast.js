const wsserver = require('websocket').server

////////////////////////////////////////////////////////////
// websocket 
////////////////////////////////////////////////////////////
let ws = null
const peers = new Map()
const broadcast = function(webserver) {
  const options = {
    httpServer: webserver,
    autoAcceptConnections: false
  }
  ws = new wsserver(options)
  ws.on('request', function(req) {
    if (!originIsAllowed(req.origin)) {
      req.reject()
      console.log(`connection from origin ${req.origin} rejected.`)
      return
    }

    const connection = req.accept('broadcast-protocol', req.origin)
    console.log(`connection accepted.`)
    console.log(`    local: ${connection.socket.localAddress}:${connection.socket.localPort}`)
    console.log(`    remote: ${connection.socket.remoteAddress}:${connection.socket.remotePort}`)
    getPeer(connection)
    listPeer()

    connection.on('message', function(msg) {
      console.log(`message: ${msg}`)
      console.log(`    type: ${msg.type}`)
      console.log(`    utf8Data: ${msg.utf8Data}`)
      console.log(`    binaryData: ${msg.binaryData}`)
      do_broadcast(connection, JSON.stringify(msg))
    })
    connection.on('close', function(reason, desc) {
      console.log(`peer(${connection.remoteAddress}) disconnected.`)
      console.log(`    ${reason}`)
      console.log(`    ${desc}`)
      removePeer(connection)
      listPeer()
    })
  })
}
function originIsAllowed(origin) {
  // TODO: origin detection implement here
  console.log(`check origin: ${origin}`)
  return true;
}
function do_broadcast(sender, data) {
  peers.forEach((p) => {
    if (p.socket.remoteAddress != sender.socket.remoteAddress ||
        p.socket.remotePort != sender.socket.remotePort) {
      p.send(data)
    }
  })
}

////////////////////////////////////////////////////////////
// utility
////////////////////////////////////////////////////////////
function getPeer(conn) {
  const local = conn.socket.localAddress + ':' + conn.socket.localPort
  const remote = conn.socket.remoteAddress + ':' + conn.socket.remotePort
  if (!peers.has(remote)) {
    peers.set(remote, conn)
  }

  return peers.get(remote)
}
function removePeer(conn) {
  const local = conn.socket.localAddress + ':' + conn.socket.localPort
  const remote = conn.socket.remoteAddress + ':' + conn.socket.remotePort
  if (!peers.has(remote)) {
    console.log(`peer not found: ${local}`)
    return
  }

  peers.delete(remote)
}
function listPeer() {
  console.log(`=======peers=======`)
  peers.forEach((p) => {
    console.log(`- ${p.socket.remoteAddress + ':' + p.socket.remotePort}`)
  })
  console.log(`===================`)
}

////////////////////////////////////////////////////////////
// module export
////////////////////////////////////////////////////////////
module.exports = broadcast
