module BoardChecker
  class Base
    def initialize(grid)
      @grid = grid
    end

    def has_winner?; end

    def execute; end
  end
end
