import pyglet
from pyglet.window import key

window = pyglet.window.Window()
keys = key.KeyStateHandler() 
window.push_handlers(keys)

if keys(key.SPACE):
    print 'ssss'