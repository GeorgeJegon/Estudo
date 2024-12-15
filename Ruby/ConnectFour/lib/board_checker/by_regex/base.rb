module BoardChecker
  module ByRegex
    class Base < ::BoardChecker::Base
      def grid_string
        @grid.flatten.join("")
      end
    end
  end
end
