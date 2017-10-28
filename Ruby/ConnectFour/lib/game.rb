require "./lib/board.rb"
require "forwardable"

class Game
  extend Forwardable

  def_delegators :@board, :board_string

  attr_reader :current_player
  def initialize
    @current_player = 1
    @currentTurn = 0
    @board = Board.new
    draw_board
  end

  def drop(column)
    puts "---------- Turn #{@currentTurn + 1} ----------"
    @board.drop(column - 1, @current_player)
    @board.errors.empty? ? next_turn : display_game_errors
    self
  end

  def draw_board
    @board.draw
  end
  protected

  def next_turn
    draw_board
    @currentTurn += 1
    @current_player = (@currentTurn % 2) + 1
  end

  def display_game_errors
    puts @board.errors.join("\n")
    @board.errors = []
  end

  private

  def winner?
    @board.win?(1) || @board.win?(2)
  end
  end
end
