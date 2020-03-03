const express = require('express')
const https = require('https')
const http = require('http')
const settings = require('./settings.json')
const broadcast = require('./services/broadcast')

const app = express()
app.set('view engine', 'ejs')
app.use(express.static(__dirname + '/public'))
app.get('/', function(req, res) {
  res.render('index.ejs')
})

let webserver = null
if (settings.secure) {
  const options = {
    key: '',
    cert: '',
  }
  webserver = https.createServer(options, app)
}
else {
  webserver = http.createServer(app)
}

broadcast(webserver)

webserver.listen(settings.port, settings.host, function() {
  console.log(`server is listening on http://${settings.host}:${settings.port}`)
})
