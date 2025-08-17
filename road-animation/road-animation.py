import time
import shutil
import sys

def animate_bar():
    width, height = shutil.get_terminal_size((80, 24))
    center = width // 2
    pos = 0

    while True:
        # Move cursor back to top-left instead of clearing
        sys.stdout.write("\033[H")
        #sys.stdout.write("\033[" + str(height//2) + ";0H")

        interval = pos % 3
        frame = []
        halfHeight = height //2
        thirdHeight = height // 3
        bar = False
        for i in range(0, height):
            if(i < thirdHeight):
              frame.append('')
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
              
            row += " " * (center - 5 - i + height//3) + "." + " " * (4 + i - height//3)
            
            if bar:
                row += "|"
            else:
                row += " "
                
            row += " " * (4 + i - height//3) + "."

            frame.append(row)

        sys.stdout.write("\n".join(frame))
        sys.stdout.flush()

        pos = (pos + 1) % height
        time.sleep(0.1)

if __name__ == "__main__":
    animate_bar()
