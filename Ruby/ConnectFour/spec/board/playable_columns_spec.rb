describe Board, "#playable_columns" do
  context "when board grid is empty" do
    it "returns all columns list" do
      expect(subject.playable_columns).to eq [0, 1, 2, 3, 4, 5, 6]
    end
  end

  context "when board grid is not empty" do
    context "and some column has at least one play" do
      before { subject.drop(0, 1) }

      it "returns all columns list" do
        expect(subject.playable_columns).to eq [0, 1, 2, 3, 4, 5, 6]
      end
    end

    context "and one column was filled" do
      before do
        Board::LINES.times { subject.drop(0,1) }
      end

      it "returns all columns list" do
        expect(subject.playable_columns).to eq [1, 2, 3, 4, 5, 6]
      end
    end

    context "and multiples columns were filled" do
      before do
        Board::LINES.times { subject.drop(0, 1) }
        Board::LINES.times { subject.drop(2, 2) }
      end

      it "returns all columns list" do
        expect(subject.playable_columns).to eq [1, 3, 4, 5, 6]
      end
    end
  end
end
