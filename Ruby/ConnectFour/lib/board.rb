class Board
  COLUMNS = 7
  LINES = 6
  attr_accessor :errors, :grid

  def initialize
    @grid   = Array.new(LINES){ Array.new(COLUMNS) { 0 } }
    @errors = []
  end

  def drop(column, symbol)
    if valid_column?(column)
      line = line_playable_column(column)
      if line
        line[column] = symbol
      else
        @errors << "Todas as linhas desta coluna já foram preenchidas"
      end
    else
      @errors << "Número de Coluna inválido!"
    end
  end
  def draw
    puts @grid.reverse.map(&method(:draw_line)).join("\n")
  end

  def board_string
    @grid.reverse.flatten.join
  end
  def set_grid(grid)
    @grid = grid.reverse
  end

  private

  def valid_column?(column)
    column.between?(0, COLUMNS)
  end

  def line_playable_column(column)
    @grid.detect { |line| line[column].zero? }
  end

  def draw_column(column)
    column.zero? ? " " : column
  end

  def draw_line(line)
    line.map(&method(:draw_column)).join("|").prepend('|').concat('|')
  end
end
