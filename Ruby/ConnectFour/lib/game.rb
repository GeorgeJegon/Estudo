require "./lib/board.rb"
require "forwardable"

class Game
  extend Forwardable

  def_delegators :@board, :board_string

  def initialize
    @board = Board.new
  end
end
