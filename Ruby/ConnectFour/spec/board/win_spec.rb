describe Board, "#win?" do
  context "when board's grid is empty" do
    it "returns false" do
      expect(subject.win?(1)).to be false
    end
  end

  context "when board's grid has one piece" do
    before { subject.drop(1, 1) }

    it "returns false" do
      expect(subject.win?(1)).to be false
    end
  end

  context "when board's grid has horizontal winner" do
    before do
      subject.set_grid([
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,1,1,1,1,0,0]
      ])
    end

    it "returns true" do
      expect(subject.win?(1)).to be true
    end
  end

  context "when board's grid has four player symbol in sequence but not in a row" do
    before do
      subject.set_grid([
        [0,0,0,0,0,1,1],
        [1,1,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0]
      ])
    end

    it "returns false" do
      expect(subject.win?(1)).to be false
    end
  end

  context "when board's grid has vertical winner" do
    before do
      subject.set_grid([
        [0,0,0,0,0,0,0],
        [0,0,0,1,0,0,0],
        [0,0,0,1,0,0,0],
        [0,0,0,1,0,0,0],
        [0,0,0,1,0,0,0],
        [0,0,0,0,0,0,0]
      ])
    end

    it "returns true" do
      expect(subject.win?(1)).to be true
    end
  end

  context "when board's grid has diagonal winner" do
    context "and it is primary" do
      before do
        subject.set_grid([
          [1,0,0,0,0,0,0],
          [0,1,0,0,0,0,0],
          [0,0,1,0,0,0,0],
          [0,0,0,1,0,0,0],
          [0,0,0,0,0,0,0],
          [0,0,0,0,0,0,0]
        ])
      end

      it "returns true" do
        expect(subject.win?(1)).to be true
      end
    end

    context "and it is primary 2" do
      before do
        subject.set_grid([
          [1,0,0,0,0,0,0],
          [0,1,0,0,0,0,0],
          [0,0,1,0,0,0,0],
          [0,0,0,1,0,0,0],
          [0,0,0,0,1,0,0],
          [0,0,0,0,0,1,0]
        ])
      end

      it "returns true" do
        expect(subject.win?(1)).to be true
      end
    end

    context "and it is secondary" do
      before do
        subject.set_grid([
          [0,0,0,0,0,0,0],
          [0,0,0,1,0,0,0],
          [0,0,1,0,0,0,0],
          [0,1,0,0,0,0,0],
          [1,0,0,0,0,0,0],
          [0,0,0,0,0,0,0]
        ])
      end

      it "returns true" do
        expect(subject.win?(1)).to be true
      end
    end
  end
end
