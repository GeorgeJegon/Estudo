describe Board do
  describe "Constants" do
    context "columns" do
      it "returns 7" do
        expect(described_class.const_get(:COLUMNS)).to eq 7
      end
    end

    context "lines" do
      it "returns 6" do
        expect(described_class.const_get(:LINES)).to eq 6
      end
    end
  end
end
