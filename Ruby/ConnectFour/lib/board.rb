class Board
  COLUMNS = 7
  LINES = 6
  def initialize
    @grid   = Array.new(LINES){ Array.new(COLUMNS) { 0 } }
  def draw
    puts @grid.reverse.map(&method(:draw_line)).join("\n")
  end

  def board_string
    @grid.reverse.flatten.join
  end
  def set_grid(grid)
    @grid = grid.reverse
  end
  def draw_column(column)
    column.zero? ? " " : column
  end

  def draw_line(line)
    line.map(&method(:draw_column)).join("|").prepend('|').concat('|')
  end
end
