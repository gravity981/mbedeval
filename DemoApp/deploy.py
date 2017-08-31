from shutil import copyfile

sourcePath = './BUILD/'
destinationPath = 'D:/'
filename = 'DemoApp-combined.hex'

print('Copy \"%s\" to %s ...' % (filename, destinationPath), end = ' ', flush = True )
try:
    copyfile(sourcePath + filename, destinationPath + filename)
    print("Done!")
except Exception:
    print("Error!")
