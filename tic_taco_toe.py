class Tic_Tac_Toe():
   def __init__(self,position,player,layout):
      self.layout = layout
      self.position = position
      self.player = player
      self.move(self.position,self.player)
      self.print_status(self.layout)
   # implementing a move
   def move(self,position,player):
      i = position/3
      j = (position%3)
      self.layout[i][j] = player

   def print_status(self, layout):
      for row in layout:
         print row
      print'\n'
# checks a winning row
def checkRow(current_status):
   for row in current_status: 
      if '_' not in row:
         if row[0] == row[1] and row[1]==row[2]:
            return row[0]
   return False
# checks a winning column
def checkColumn(current_status):
   for c in range(3):
      column = []
      for row in range(3):
         if current_status[row][c]!='_':
            column.append(current_status[row][c])
            if len(column) == 3:
               if column[0]==column[1] and column[1]==column[2]:
                  return column[0]
   return False

# checks a winning diagonal
def checkLeadingDiagonal(current_status):
   diagonal = []
   for r in range(3):
      for c in range(3):
         if r==c and current_status[r][c]!='_':
            diagonal.append(current_status[r][r])
   if len(diagonal)==3:
      if diagonal[0] == diagonal[1] and diagonal[1]==diagonal[2]:
         return diagonal[0]  
   return False

# checks a winning reverse diagonal
def checkReverseDiagonal(current_status):
   diagonal = []
   for r in range(3):
      if current_status[r][2-r]!='_':
         diagonal.append(current_status[r][2-r])

   if len(diagonal)==3:
      if diagonal[0] == diagonal[1] and diagonal[1]==diagonal[2]:
         return diagonal[0]     
   return False

# checks if the puzzle is complete ->  to be used especially to determine cases of a draw
def complete(current_status):
   count = 0
   for row in current_status:
      if '_' not in row:
         count+=1
   if count == 3:
      return True
   return False

if __name__ == '__main__': 

   layout = [['_','_','_'],['_','_','_'],['_','_','_']]
   # display the arrangement of positions.. in the format [[0,1,2],[3,4,5],[6,7,8]]
   print 'Positions arrangement :'
   for i in [0,3,6]:
      print range(i,i+3)
      
   print 'Type the position you wish to play :'
   impossible = []  
   round = 0        # keeps count of the number of rounds played. X and O will alternate in rounds
   while 1:  
      # alternating players. X starts the game
      if round == 0 or round%2==0:
         player = 'X'
      else:
         player = 'O'
      position = input'Player {}\'s turn :'.format(player)   # input the position you want to play

      if position not in impossible:
         impossible.append(position)    # to store positions that have been played, else Impossible move!!!
            
         if position in range(9):
            Tic_Tac_Toe(position,player,layout)
            round+=1
       
         else:
            print 'Scope Error : Input a number between 0 and 8'
      
      else:
         print 'Impossible move!!'
         continue
     
      if checkRow(layout):
         print '{} Wins'.format(checkRow(layout))
         break
      if checkColumn(layout):
         print '{} Wins'.format(checkColumn(layout))
         break
      if checkLeadingDiagonal(layout):
         print '{} Wins'.format(checkLeadingDiagonal(layout))
         break
      if checkReverseDiagonal(layout):
         print '{} Wins'.format(checkReverseDiagonal(layout))
         break
      if complete(layout):
         print 'Draw!'
         break 










   
