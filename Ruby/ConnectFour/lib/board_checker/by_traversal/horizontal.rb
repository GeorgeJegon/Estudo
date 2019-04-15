module BoardChecker
  module ByTraversal
    class Horizontal < ::BoardChecker::Base

      def has_winner?
        @matches.any?
      end

      def execute
        @matches = []

        @grid.each.with_index do |column, line_index|
          column_len = column.length
          column.each_with_index do |cell, column_index|
            next if cell.zero? || !(0..column_len).member?(column_index + 3)

            score = visit_neighborhoods(0, 1,cell, line_index, column_index)
            @matches << { line: line_index, column: column_index, score: score, cell: cell } if score >= 4
          end
        end
      end

      private

      def visit_neighborhoods(line_step, column_step, cell, line, column)
        line += line_step
        column += column_step

        return 1 unless @grid[line][column] == cell

        visit_neighborhoods(line_step, column_step, cell, line, column) + 1
      end
    end
  end
end
