module BoardChecker
  class Base
    def initialize(grid)
      @grid = grid
    end

    def has_winner?
      raise NotImplementedError, "Method #{__method__} need to be implemented"
    end

    def execute
      raise NotImplementedError, "Method #{__method__} need to be implemented"
    end
  end
end
