from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

## Example Agent
class ReflexAgent(Agent):

  def Action(self, gameState):

    move_candidate = gameState.getLegalActions()

    scores = [self.reflex_agent_evaluationFunc(gameState, action) for action in move_candidate]
    bestScore = max(scores)
    Index = [index for index in range(len(scores)) if scores[index] == bestScore]
    get_index = random.choice(Index)

    return move_candidate[get_index]

  def reflex_agent_evaluationFunc(self, currentGameState, action):

    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    oldFood = currentGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    return successorGameState.getScore()



def scoreEvalFunc(currentGameState):

  return currentGameState.getScore()

class AdversialSearchAgent(Agent):

  def __init__(self, getFunc ='scoreEvalFunc', depth ='2'):
    self.index = 0
    self.evaluationFunction = util.lookup(getFunc, globals())
    self.depth = int(depth)



class MinimaxAgent(AdversialSearchAgent):
  """
    [문제 01] MiniMaxAgent의 Action을 구현하시오.
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    ### Max함수와 Min함수가 필요하다. ###
    def Max_Value(state, depth):
      ### terminal-test ###
      if state.isWin() or state.isLose():
        return state.getScore()
      ### v = -inf ###
      high_value = float("-inf")
      ### 0은 human을 나타낸다. human이 할 수 있는 action 초기화 ###
      actions = state.getLegalActions(0)
      for i in actions:
        ### v = MAX(v,Min-Value(result(s,a))) 자식들의 최소값 중 가장 큰 값 ###
        ### generateSuccessor는 행동을 했을 때 state를 return한다. human은 0이다. ###
        value = Min_Value(state.generateSuccessor(0, i), depth, 1)
        if value > high_value:
          high_value = value
          action = i
      ### 가장 작은 ghost value 중 가장 큰 value값을 반환한다. ###
      if depth == 0:
        return action
      else:
        return high_value

    
    def Min_Value(state, depth, ghost):
      ### terminal-test ###
      if state.isLose() or state.isWin():
        return state.getScore()
      ### v = inf ###
      low_value = float("inf")
      ### ghost가 할 수 있는 action 초기화 ###
      actions = state.getLegalActions(ghost)
      for i in actions:
        ### 마지막 ghost를 판별해야한다. getNumAgents는 human+ghost이므로 -1해서 판단한다. 마지막 ghost가 아니면 else문에서 다음 ghost를 구한다. ###
        if state.getNumAgents() - 1 == ghost: 
          ### 마지막 ghost면 depth를 판별한다. 만약 depth=4라면 0~3이므로 -1해서 판단한다. ###
          if depth == self.depth-1:
            ### 마지막 depth라면 AdversialSearchAgent에서 선언한 evaluationFunction을 이용해 score를 평가한다 ###
            value = self.evaluationFunction(state.generateSuccessor(ghost, i))
          else:
            ### 마지막 depth가 아니라면 다음 depth를 구한다 ###
            value = Max_Value(state.generateSuccessor(ghost, i), depth + 1)
        else:
          value = Min_Value(state.generateSuccessor(ghost, i), depth, ghost+1)
        low_value = min(low_value,value)
      ### ghost의 value 중 가장 작은 값을 반환한다. ###
      return low_value

    return Max_Value(gameState, 0)




    ############################################################################




class AlphaBetaAgent(AdversialSearchAgent):
  """
    [문제 02] AlphaBetaAgent의 Action을 구현하시오.
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    
    ### 위에서 작성한 MinimaxAgent에 주석 처리된 곳을 추가한다. 주석 부분을 제외하면 MinimaxAgent와 동일하다. ###
    ### 기존 MinimaxAgent에서 상관 없는 부분을 판단하는 a,b 값을 parameter로 넘겨준다. ###
    def Max_Value(state, depth, a, b):
      if state.isWin() or state.isLose():
        return state.getScore()
      high_value = float("-inf")
      a = float("-inf")
      actions = state.getLegalActions(0)
      for i in actions:
        value = Min_Value(state.generateSuccessor(0, i), depth, 1,a,b)
        if value > high_value:
          high_value = value
          action = i
        ###a,b를 추가하여 상관 없는 부분은 날려준다. ###
        ### a는 Min_Value에서 low_value와 비교되어 최소값보다 크면 날아간다 ###
        a = max(a,high_value)
        if high_value > b:
          return high_value
      if depth == 0:
        return action
      else:
        return high_value
    
    def Min_Value(state, depth, ghost, a, b):
      if state.isLose() or state.isWin():
        return state.getScore()
      low_value = float("inf")
      b = float("inf")
      actions = state.getLegalActions(ghost)
      for i in actions:
        if state.getNumAgents() - 1 == ghost: 
          if depth == self.depth - 1:
            value = self.evaluationFunction(state.generateSuccessor(ghost, i))
          else:
            value = Max_Value(state.generateSuccessor(ghost, i), depth + 1,a,b)
        else:
          value = Min_Value(state.generateSuccessor(ghost, i), depth, ghost+1,a,b)
        low_value = min(low_value,value)
        ### a,b를 추가하여 상관 없는 부분은 날려준다. ###
        ### b는 Max_Value에서 high_value와 비교되어 최대값보다 작으면 날아간다 ###
        b = min(b,low_value)
        if low_value < a:
          return low_value          
      return low_value
    return Max_Value(gameState, 0,float("-inf"),float("inf"))



    ############################################################################



class ExpectimaxAgent(AdversialSearchAgent):
  """
    [문제 03] ExpectimaxAgent의 Action을 구현하시오.
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    ### Expectimax는 chance nodes에 연결된 모든 successor를 판단해야 한다. ###
    ### max에서 선택할 때 min에서 나온 값의 평균 기댓값을 바탕으로 선택한다. ###
    ### 따라서 '1/(ghost가 취할 수 있는 action의 수)*value값'을 해주어 더한 평균값을 바탕으로 max에서 판단한다. ###
    ### ExpectimaxAgent도 주석 부분을 제외하면 MinimaxAgent와 동일하다. ###
    def Max_Value(state, depth):
      if state.isWin() or state.isLose():
        return state.getScore()
      high_value = float("-inf")
      actions = state.getLegalActions(0)
      for i in actions:
        value = Min_Value(state.generateSuccessor(0, i), depth, 1)
        if value > high_value:
          high_value = value
          action = i
      if depth == 0:
        return action
      else:
        return high_value
    
    def Min_Value(state, depth, ghost):
      if state.isLose() or state.isWin():
        return state.getScore()
      value = float("inf")
      actions = state.getLegalActions(ghost)
      ### value의 평균값을 구하기 위해 몇 가지의 경우가 있는지 구한다 ###
      p = 1/len(actions)
      for i in actions:
        if state.getNumAgents() - 1 == ghost: 
          if depth == self.depth - 1:
            value = self.evaluationFunction(state.generateSuccessor(ghost, i))
            ### value값에 p를 곱한 것을 더해 평균값을 구한다. ###
            value += p*value
          else:
            value = Max_Value(state.generateSuccessor(ghost, i), depth + 1)
            value += p*value
        else:
          value = Min_Value(state.generateSuccessor(ghost, i), depth, ghost+1)
          value += p*value
      return value
    return Max_Value(gameState, 0)


    ############################################################################
