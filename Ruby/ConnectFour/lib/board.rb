class Board
  COLUMNS = 7
  LINES = 6
  def initialize
    @grid   = Array.new(LINES){ Array.new(COLUMNS) { 0 } }
  end
end
