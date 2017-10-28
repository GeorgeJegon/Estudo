require "./lib/board.rb"
require "forwardable"

class Game
  extend Forwardable

  def_delegators :@board, :board_string

  def initialize
    @currentTurn = 0
    @board = Board.new
    draw_board
  def draw_board
    @board.draw
  end
  protected

  def next_turn
    draw_board
    @currentTurn += 1
    @current_player = (@currentTurn % 2) + 1
  end
  end
end
