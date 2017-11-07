require "board_checker"

class Board
  COLUMNS = 7
  LINES = 6

  STRATEGIES = {
   by_regex: BoardChecker::ByRegex
  }.freeze

  attr_accessor :errors, :grid

  def initialize
    @grid   = Array.new(LINES){ Array.new(COLUMNS) { 0 } }
    @strategy = STRATEGIES[:by_regex]
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

  def win?(player_index)
    @strategy.constants.reject(&method(:base_const?))
                       .map(&method(:init_strategy_class))
                       .each(&:execute)
                       .map(&:has_winner?).any?
  end

  def set_grid(grid)
    @grid = grid.reverse
  end

  private

  def base_const?(const)
    const == :Base
  end

  def init_strategy_class(const)
    @strategy.const_get(const).new(@grid.reverse)
  end

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
