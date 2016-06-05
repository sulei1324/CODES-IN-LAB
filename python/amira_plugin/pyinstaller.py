import  os

if __name__ == '__main__':
    from PyInstaller.main import run
    opts=['qttest.py','-D','-w']
    run(opts)
