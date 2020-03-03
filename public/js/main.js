window.onload = boot

function boot() {

  addElementEvent('start', 'click', start)
  addElementEvent('stop', 'click', stop)
  addElementEvent('send', 'click', send)

  connect_ws()
  open_media()
}

async function start() {
  const ret = await open_media()

  createPeer()
}

function stop() {
  close_media()
}

function send() {
  send_input_message()
}

////////////////////////////////////////////////////////////
// websocket functions
////////////////////////////////////////////////////////////
let client = null
function connect_ws() {
  if (client) {
    return
  }

  client = new WebSocket('ws:localhost:8080', 'broadcast-protocol')

  client.onerror = function(e) {
    console.log(`connection error: `, e)
  }
  client.onopen = function(e) {
    debug(`websocket is connected: `, e)
  }
  client.onclose = function(e) {
    console.log(`broadcast-protocol connection closed: `, e)
  }
  client.onmessage = function(e) {
    debug(`message from server: `, e)
    debug(`    type: ${e.type}`)
    const data = JSON.parse(e.data)
    debug(`    data: `, data)
    debug(`    data:type: ${data.type}`)
    debug(`    data:utf8Data: ${data.utf8Data}`)
    debug(`    data:binaryData: ${data.binaryData}`)
  }
}
function send_input_message() {
  const message = getText('message')
  debug(`message: ${message}`)
  debug(`client: `, client)

  if (!client) {
    console.log(`websocket is not connected.`)
    return
  }
  if (client.readyState === client.OPEN) {
    client.send(message)
  }
}
function send_data(data) {
  debug(`message: `, data)

  if (!client) {
    console.log(`websocket is not connected.`)
    return
  }
  if (client.readyState === client.OPEN) {
    client.send(JSON.stringify(data))
  }
}
////////////////////////////////////////////////////////////
// media manipulate
////////////////////////////////////////////////////////////
let stream_local = null
async function open_media() {
  if (stream_local) {
    debug(`already stream is open`)
    return true
  }
  await navigator.mediaDevices.getUserMedia({video:true})
  .then((stream) => {
    debug(`local stream is now open.`)
    getElement('localVideo').srcObject = stream
    stream_local = stream
    return true
  })
  .catch((e) => {
    debug(`local stream is failed to open. ${e}`)
    return false
  })
}

function close_media() {
  debug(`close media`)
  getElement('localVideo').pause()
  getElement('localVideo').srcObject = null
  stream_local = null
}

////////////////////////////////////////////////////////////
// peer connection
////////////////////////////////////////////////////////////
let peer = null
function createPeer() {
  const config = {
    iceServers: [
      {
        urls: 'stun:stun.l.google.com:19302'
      }
    ]
  }
  peer = new RTCPeerConnection(config)

  // register peer event handler
  peer.addEventListener('icecandidate', on_icecandidate)
  peer.addEventListener('negotiationneeded', on_negotiationneeded)
  peer.addEventListener('track', on_track)

  // add track to peer
  if (stream_local) {
    stream_local.getTracks().forEach(track => {
      peer.addTrack(track, stream_local)
    })
  }
}
async function sendOffer() {
  const offer = await peer.createOffer()
  await peer.setLocalDescription(offer)

  console.log(`offer: `, offer)

  const data = {
    type: 'offer',
    data: offer
  }
  send_data(data)
}
function on_icecandidate(e) {
  console.log(`on_icecandidate `, e.candidate)
  if (e.candidate) {
    const data = {
      type: 'candidate',
      data: e.candidate
    }
    send_data(data)
  }
}
async function on_negotiationneeded(e) {
  console.log(`on_negotiationneeded`)
  await sendOffer()
}
function on_track(e) {
  // TODO: no remote video
  console.log(`on_track`)
}

////////////////////////////////////////////////////////////
// utility
////////////////////////////////////////////////////////////
function getElement(id) {
  return document.getElementById(id)
}
function getText(id) {
  return getElement(id).value
}
function addElementEvent(id, event, fn) {
  getElement(id).addEventListener(event, fn)
}
function pad(x, size, fill) {
  return ('' +x).padStart(size, fill)
}
const pad40 = function (x) {
  return pad(x, 4, '0')
}
const pad30 = function (x) {
  return pad(x, 3, '0')
}
const pad20 = function (x) {
  return pad(x, 2, '0')
}
function now() {
  const now = new Date()
  return `${pad40(now.getFullYear())}-${pad20(now.getMonth()+1)}-${pad20(now.getDate())}`
  + ` ${pad20(now.getHours())}:${pad20(now.getMinutes())}:${pad20(now.getSeconds())}:${pad30(now.getMilliseconds())}`
}
function debug(msg, opt) {
  if (arguments.length == 1)
    console.log(`[${now()}] ${msg}`)
  else
    console.log(`[${now()}] ${msg}`, opt)
}