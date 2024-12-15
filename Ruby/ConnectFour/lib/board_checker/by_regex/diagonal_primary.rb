module BoardChecker
  module ByRegex
    class DiagonalPrimary < Base
      REGEX_DEFINITION = {
        filter: /((?:1\d{7}){3}(?:1\d{0,3})+)/ ,
        group: /(1)\d{0,7}/
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
