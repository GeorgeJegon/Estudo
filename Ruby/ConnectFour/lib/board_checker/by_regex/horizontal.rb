module BoardChecker
  module ByRegex
    class Horizontal < Base
      REGEX_DEFINITION = /(1{4,}|2{4,})/

      @matches = []

      def has_winner?
        @matches.any?
      end

      def execute
        @matches = @grid.map do |row|
          row.join("").to_enum(:scan, REGEX_DEFINITION).map { Regexp.last_match }
        end.flatten.compact.sort_by { |match| match[1].length }
      end

      def longest_match
        @longest_match ||= @matches.first
      end

      def winner_player
        longest_match[1]
      end
    end
  end
end
