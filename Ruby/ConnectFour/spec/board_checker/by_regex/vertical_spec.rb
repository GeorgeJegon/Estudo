describe BoardChecker::ByRegex::Vertical do
  let(:grid) { Array.new(6){ Array.new(7) { 0 } }  }

  subject { described_class.new(grid) }

  describe "#has_winner?" do
    before { subject.execute }

    context "when grid is empty" do
      it "returns false" do
        expect(subject.has_winner?).to be false
      end
    end

    context "when grid has one play" do
      let(:grid) do
        [
          [1,0,0,0,0,0,0],
          [0,0,0,0,0,0,0],
          [0,0,0,0,0,0,0],
          [0,0,0,0,0,0,0],
          [0,0,0,0,0,0,0],
          [0,0,0,0,0,0,0]
        ]
      end

      it "returns false" do
        expect(subject.has_winner?).to be false
      end
    end

    context "when grid has four player symbol in sequence" do
      context "and it is vertical" do
        let(:grid) do
          [
            [0,0,0,0,0,0,0],
            [1,0,0,0,0,0,0],
            [1,0,0,0,0,0,0],
            [1,0,0,0,0,0,0],
            [1,0,0,0,0,0,0],
            [0,0,0,0,0,0,0]
          ]
        end

        it "returns true" do
          expect(subject.has_winner?).to be true
        end
      end

      context "and it is vertical" do
        let(:grid) do
          [
            [0,0,0,1,0,0,0],
            [0,0,1,1,1,0,0],
            [0,0,1,1,1,0,0],
            [0,0,1,1,1,0,0],
            [0,0,1,1,1,0,0],
            [0,0,1,1,1,0,0]
          ]
        end

        it "returns true" do
          expect(subject.has_winner?).to be true
        end
      end
    end
  end
end