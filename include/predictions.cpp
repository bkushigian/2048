#include "predictions.hpp"


double evalBoard(board_2048 b){
   // Just evaluate the number of empties.
   double score = 0;
   switch (evaluationMode){
      case MAX_EMPTIES: return maxEmpties(b);
      case MAX_MERGES:  return maxMerges(b);
      case BASTARD_01:   return bastard01(b);
      default: return maxEmpties(b);
   }
}

double maxEmpties(board_2048 b){
   double score = 0;

   if ( b.inCorner( b.getHighestVal() ) )
      score += highValInCorner;
   if (b.isNormal() && !b.isGridlocked()) score += normalNotGridlocked;
   score += b.getPosOfEmpty().size();
   if (b.getPosOfEmpty().size() < MIN_EMPTIES && std::max(b.numberOfMerges(LEFT), b.numberOfMerges(UP)) < 2)
      score -= (MIN_EMPTIES - b.getPosOfEmpty().size()) * badEmptyValue;
   score += log(b.getHighestVal()) * .2;
   return score;
}


double maxMerges(board_2048 b){
   return std::max(b.numberOfMerges(LEFT), b.numberOfMerges(UP));
}

double bastard01(board_2048 b){
   double score = 0;
   score += scoreFactor * log(b.getScore());

   if ( b.inCorner( b.getHighestVal() ) )
      score += highValInCorner;
   score += .5 * std::max( b.numberOfMerges(LEFT), b.numberOfMerges(UP));
   score += b.getPosOfEmpty().size();
   if (b.isNormal() && ! b.isGridlocked())
      score += normalNotGridlocked;
   score += b.normality();
   if (b.getPosOfEmpty().size() < MIN_EMPTIES && std::max(b.numberOfMerges(LEFT), b.numberOfMerges(UP)) < 2)
      score -= b.getPosOfEmpty().size() * badEmptyValue;
   return score;
}

direction_t   predChooseMove(board_2048 b, int depth){
   double left = -1.0, right = -1.0, up = -1.0, down = -1.0;
   board_2048 moveBoard;
   //if (b.getPosOfEmpty().size() >= 8) depth = 1;
   //if (b.getPosOfEmpty().size() >= 6 && depth > 2) depth = 2;
   if (b.isValidMove(LEFT)){
      moveBoard = b;
      moveBoard.moveNoSpawn(LEFT);
      left = evalBoard(moveBoard, depth);
   }
   if (b.isValidMove(RIGHT)){
      moveBoard = b;
      moveBoard.moveNoSpawn(RIGHT);
      right = evalBoard(moveBoard, depth);
   }
   if (b.isValidMove(DOWN)){
      moveBoard = b;
      moveBoard.moveNoSpawn(DOWN);
      down = evalBoard(moveBoard, depth);
   }
   if (b.isValidMove(UP)){
      moveBoard = b;
      moveBoard.moveNoSpawn(UP);
      up = evalBoard(moveBoard, depth);
   }
   if (left > right && left > down && left > up)   return LEFT;
   if (right > down && right > up)                 return RIGHT;
   if (up > down)                                  return UP;
   return DOWN;
}


double evalBoard(board_2048 b, int depth){
   if (depth == 0) return evalBoard(b);
   // Depth greater than 1;
   board_2048 moveBoard;
   double left = 0.0, right = 0.0, up = 0.0, down = 0.0;
   std::vector<int> empties;
   // Test Left Direction.
   moveBoard = b;
   moveBoard.moveNoSpawn(LEFT);
   empties = moveBoard.getPosOfEmpty();
   if (empties.size() != 0){
      for (int i = 0; i < empties.size(); ++i){
         moveBoard.setVal(empties[i],2);
         left += evalBoard(moveBoard, depth - 1) * twosFactor;
         if (PRECISE_EVALUATION){
            moveBoard.setVal(empties[i],4);
            left += evalBoard(moveBoard, depth - 1) * foursFactor;
         }
         moveBoard.setVal(empties[i], 0);
      }
      left /= empties.size();
   }

   // Test Right Direction
   moveBoard = b;
   moveBoard.moveNoSpawn(RIGHT);
   empties = moveBoard.getPosOfEmpty();
   if (empties.size() != 0){
      for (int i = 0; i < empties.size(); ++i){
         moveBoard.setVal(empties[i],2);
         right += evalBoard(moveBoard, depth - 1) * twosFactor;
         if (PRECISE_EVALUATION){
            moveBoard.setVal(empties[i],4);
            right == evalBoard(moveBoard, depth - 1) * foursFactor;
         }
         moveBoard.setVal(empties[i],0);
      }
      right /= empties.size();
   }

   moveBoard = b;
   moveBoard.moveNoSpawn(UP);
   empties = moveBoard.getPosOfEmpty();
   if (empties.size() != 0){
      for (int i = 0; i < empties.size(); ++i){
         moveBoard.setVal(empties[i],2);
         up += evalBoard(moveBoard, depth - 1) * twosFactor;
         if (PRECISE_EVALUATION){
            moveBoard.setVal(empties[i], 4);
            up += evalBoard(moveBoard,depth - 1) * foursFactor;
         }
         moveBoard.setVal(empties[i],0);
      }
      up /= empties.size();
   }


   moveBoard = b;
   moveBoard.moveNoSpawn(DOWN);
   empties = moveBoard.getPosOfEmpty();
   if (empties.size() != 0){
      for (int i = 0; i < empties.size(); ++i){
         moveBoard.setVal(empties[i],2);
         down += evalBoard(moveBoard, depth - 1) * twosFactor;
         if (PRECISE_EVALUATION){
            moveBoard.setVal(empties[i], 4);
            down += evalBoard(moveBoard, depth - 1) * foursFactor;
         }
         moveBoard.setVal(empties[i],0);

      }
      down /= empties.size();
   }

   if (left > right){
      if (left > up){
         if (left > down) return left;
         return down;
      }
      if (up > down) return up;
      return down;
   }
   if (right > up){
      if (right > down)return right;
      return down;
   }
   if (up > down) return up;
   return down;
}
