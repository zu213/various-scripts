import time
import shutil
import sys
import random
import math

def append_mountains(thirdHeight, width):
  frame = [""] * thirdHeight
  mountainAngle = thirdHeight / (width / 4)
  charLeft = ''
  charRight = ''
  if mountainAngle < 0.5:
    charLeft = '-'
    charRight = '-'
  elif mountainAngle < 1:
    charLeft = '/'
    charRight = '\\'
  else:
    charLeft = '|'
    charRight = '|'
  
  currentHeight = thirdHeight - 1
  goingUp = True
  
  print(mountainAngle)
  for i in range(0, width):
    rowPainted = False
    for j in range(0, thirdHeight):
      if not rowPainted and j == math.floor(currentHeight):
        rowPainted = True
        if (not goingUp and j == thirdHeight - 1) or (goingUp and j == 0) or random.randint(1, 8) == 8:
          goingUp = not goingUp
        if goingUp:
          frame[j] += charLeft
          currentHeight -= mountainAngle
        else:
          frame[j] += charRight
          currentHeight += mountainAngle
      else:
        frame[j] += " "
  
  return frame

def animate_bar():
    width, height = shutil.get_terminal_size((80, 24))
    center = width // 2
    pos = 0
    
    initialFrame = append_mountains(height//3, width - 1)

    while True:
        # Move cursor back to top-left instead of clearing
        print("\033[H", end="", flush=True)
        sys.stdout.flush()
        #sys.stdout.write("\033[" + str(height//2) + ";0H")

        interval = pos % 3
        thirdHeight = height // 3
        
        frame = initialFrame[:]
        
        bar = False
        for i in range(thirdHeight - 1, height):
            if(i == thirdHeight - 1):
              frame.append("-" * (width - 1))
              continue
            
            row = ""

            if(i < thirdHeight * 2):
              if (i - interval) % 3 == 0 and i > thirdHeight:
                bar = True
              else:
                bar = False
            else:
              if (i - (interval + 1)) % 4 == 0 or (i - (interval + 1)) % 4 == 1:
                bar = True
              else:
                bar = False
              
            row += " " * (center - 3 - i + height//3) + "." + " " * (2 + i - height//3)
            
            if bar:
                row += "|"
            else:
                row += " "
                
            row += " " * (2 + i - height//3) + "."

            frame.append(row)

        sys.stdout.write("\n".join(frame))
        sys.stdout.flush()

        pos = (pos + 1) % height
        time.sleep(0.1)

if __name__ == "__main__":
    animate_bar()
