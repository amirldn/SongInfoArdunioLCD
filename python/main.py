import serial
import spotipy
from spotipy.oauth2 import SpotifyOAuth
import time
import json

# export SPOTIPY_CLIENT_ID='3c0c69295bd34f8db54b0ee6ad2f0a1f'
# export SPOTIPY_CLIENT_SECRET='your-spotify-client-secret'
# export SPOTIPY_REDIRECT_URI='http://localhost/'


class currentPlaying:
    def f(self):
        self.update()
        return

    def update(self):
        currentPlaying = sp.current_user_playing_track()
        # print(currentPlaying)
        if currentPlaying == 'None':
            print("Nothing Playing")
            return None
        timeMs = int(currentPlaying['progress_ms'])
        self.timeSec = int((timeMs / 1000) % 60)
        if len(str(self.timeSec)) == 1:
            self.timeSec = '0' + str(self.timeSec)
        self.timeMin = int((timeMs / (1000*60)) % 60)
        self.title = currentPlaying["item"]["name"]
        self.artist = currentPlaying["item"]["artists"][0]['name']
        return 1


arduino = serial.Serial('/dev/cu.usbmodem1301',
                        baudrate=9600,
                        timeout=.5)
print('Using', arduino.name)

scope = "user-read-currently-playing"
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(scope=scope))
cp = currentPlaying()


while True:
    data = arduino.readline()
    print(str(data))

    if cp.update() != None:
        print(str(cp.timeMin) + ":" + str(cp.timeSec) +
              " " + cp.title + " " + cp.artist)
        arduino.write(('1 NAME:{name} ARTIST:{artist} MIN:{min} SEC:{sec};'.format(
            name=cp.title, artist=cp.artist, min=cp.timeMin, sec=cp.timeSec)).encode())
    else:
        arduino.write(b'0 TIME:12:38 DATE:17/04/2022;')
    time.sleep(1)
ç
