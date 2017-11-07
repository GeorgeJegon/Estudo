module BoardChecker
  module ByRegex
    class DiagonalSecondary < Base
      REGEX_DEFINITION = {
        filter: /((?:1\d{5}){3}(?:1\d{3,5})+)/ ,
        group: /(1)\d{0,5}/
      }.freeze

      @matches = []

      def has_winner?
        @matches.any?
      end

      def execute
        @matches = grid_string.to_enum(:scan, REGEX_DEFINITION[:filter]).map { Regexp.last_match }.map { |match| match.to_s.scan(REGEX_DEFINITION[:group]).flatten.join("") }
      end
    end
  end
end
