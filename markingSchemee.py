import os

#checking if the person has only played one move and has not ovewritten another player
def validMove(previous, current):
  differences = 0
  for a in range(0,len(previous)):
    temp = [i for i in previous[a]+current[a] if i not in previous[a] or i not in current[a]]
    differences += len(temp)
    if differences > 1:
      return False
  for i in range(0,len(previous)):
    for j in range(0,len(previous[0])):
       if previous[i][j] != current[i][j] and previous[i][j] != '0':
         return False
  return True

#checking if there is a horizontal group that wins
def checkHorizontal(board, required):
  for row in board:
    temp = []
    for elem in row:
      if elem != '0':
        if len(temp) and elem == temp[-1]:
           temp.append(elem)
        else:
           temp = []
           temp.append(elem)
        if len(temp) == required:
           return temp[-1]
  return '0'
#checking if there is a vertical group
def checkVertical(Board, required):
  for a in range(0,len(Board[0])):
    temp = []
    for row in Board:
      if row[a] != '0':
        if len(temp) and row[a] == temp[-1]:
          temp.append(row[a])
        else:
          temp = []
          temp.append(row[a])
        if len(temp) == required:
          return temp[-1]
  return '0'
'''
1 2 3 4 5
6 7 8 9 10
1 2 3 4 5
1 2 3 5 1
'''
# using the above example checking the diagonals like 1,7,3,5
def checkLeadingDiagonals(Board, required):
  for a in range(0 , len(Board[0])):
    temp = []
    for b in range(0, len(Board)):
      if b+a < len(Board[0]):
        if Board[b][b+a] != '0':
          if len(temp) and Board[b][b+a] == temp[-1]:
            temp.append(Board[b][b+a])
          else:
            temp = []
            temp.append(Board[b][b+a])
          if len(temp) == required:
            return temp[-1]
  return '0'

#using above example checking diagonals that go like 4 8 2 1
def checkReverseDiagonals(Board, required):
  for a in range(0 , len(Board[0])):
    temp = []
    for b in range(0, len(Board)):
      if  a-b >= 0:
        if Board[b][a-b] != '0':
          if len(temp) and Board[b][a-b] == temp[-1]:
            temp.append(Board[b][a-b])
          else:
            temp = []
            temp.append(Board[b][a-b])
          if len(temp) == required:
            return temp[-1]
  return '0'
def checkFullBoard(Board):
  for a in Board:
    for b in a:
      if b == '0':
        return True
  return False

def main():
  prevboard = []
  board = []
  stringrep = ''
  width = 7
  towin = 4
  for i in range (0,width):
    nrow = ''
    for j in range(0,width):
      nrow = nrow + '0'
    stringrep = stringrep +nrow
    board.append(nrow)
    prevboard.append(nrow)

  f = open('playingground.txt','w+')
  f.write(stringrep)
  f.close()
  com1 = './p1 '+str(width)+' '+str(towin)+' '+stringrep+' x > playingground.txt'
  com2 = './p2 '+str(width)+' '+str(towin)+' '+stringrep+' o > playingground.txt'
  winner = '0'
  position = 0
  while winner == '0' and checkFullBoard(board):
    f = open ('playingground.txt','r')
    stringrep = f.read()
    f.close()
    tempboard = ''
    pi = 0
    pos = 0
    print(len(stringrep))
    for elem in stringrep:
      print(pi)
      pi+=1
      tempboard = str(tempboard) + str(elem)
      if len(tempboard) == width:
        print (len(tempboard))
        board[pos] = tempboard
        pos+=1
        print(pos)
        tempboard = ''

    if validMove(prevboard,board):
      prevboard = board
      winner = checkVertical(board,towin)
      if(winner != '0'):
        break
      winner = checkHorizontal(board,towin)
      if(winner != '0'):
        break
      winner = checkLeadingDiagonals(board,towin)
      if(winner != '0'):
        break
      winner = checkReverseDiagonals(board,towin)
      if(winner != '0'):
        break
    if position == 0:
      com1 = './p1 '+str(width)+' '+str(towin)+' '+stringrep+' x > playingground.txt'
      os.system(com1)
      position = 1
    else:
      com1 = './p1 '+str(width)+' '+str(towin)+' '+stringrep+' o > playingground.txt'
      os.system(com1)
      position = 0


  print("The winner is "+winner)
  for line in board:
    print (line)


if __name__ == '__main__':
  main()
