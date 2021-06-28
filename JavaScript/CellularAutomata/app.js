function CellularAutomata(options) {
  options = options ||  {}

  this.populations = options.populations || 101
  this.generations = options.generations || 100
  this.randomInitialPosition = options.randomInitialPosition !== undefined ? options.randomInitialPosition : true
  this.gridStates  = []
  this.rule = options.rule || 101
  this.intervalID = null
  this.neighborhoodsDefinition = [
    { x: -1, y: -1 },
    { x:  0, y: -1 },
    { x:  1, y: -1 }
  ]
}

CellularAutomata.ruleStateNeighborsDefinitions = [
  [1,1,1],
  [1,1,0],
  [1,0,1],
  [1,0,0],
  [0,1,1],
  [0,1,0],
  [0,0,1],
  [0,0,0]
]

CellularAutomata.prototype.getNeighborhoodsStates = function(pastGenerationStates, index) {
  return this.neighborhoodsDefinition.map(function(neighborhoodDefinition) {
    let neighborhoodIndex = index + neighborhoodDefinition.x

    if  (neighborhoodIndex < 0) {
      neighborhoodIndex = this.populations - 1
    } else if (neighborhoodIndex >= this.populations) {
      neighborhoodIndex = 0
    }

    return pastGenerationStates[neighborhoodIndex]
  }.bind(this));
};

CellularAutomata.prototype.step = function(currentGeneration) {
  let pastGenerationStates = this.gridStates[currentGeneration - 1];
  let currentGenerationStates = pastGenerationStates.slice();

  return currentGenerationStates.map(function(state, index) {
    let neighborhoodsStates = this.getNeighborhoodsStates(pastGenerationStates, index)
    return this.applyRule(neighborhoodsStates, state)
  }.bind(this));
};

CellularAutomata.prototype.applyRule = function(neighborhoodsStates, currentState) {
  let ruleStates = Number(this.rule).toString(2).padStart("8", 0).split("").map(Number)

  for(let i = 0, j = CellularAutomata.ruleStateNeighborsDefinitions.length; i < j; i++) {
    let ruleDefinition = CellularAutomata.ruleStateNeighborsDefinitions[i]
    if (
      (neighborhoodsStates[0] == ruleDefinition[0]) &&
      (neighborhoodsStates[1] == ruleDefinition[1]) &&
      (neighborhoodsStates[2] == ruleDefinition[2])
    ) {

      return ruleStates[i]
    }
  }
  return currentState;
};

CellularAutomata.prototype.neighborhoods = function() {

};

CellularAutomata.prototype.createFirstGeneration = function() {
  if (this.randomInitialPosition) {
    return Array.from(Array(this.populations)).map(()=> Math.round(Math.random()))
  } else {
    return Array.from(Array(this.populations)).map(function(element, index) {
      return Math.floor(this.populations/2) == index;
    }.bind(this))
  }
}

CellularAutomata.prototype.createCellElement = function(state) {
  let cell = document.createElement("div")
  cell.classList.add("automata-cell", state ? "active" : "inactive")
  return cell
};

CellularAutomata.prototype.drawRow = function(DOMElement, listCellStates) {
  let frag = document.createDocumentFragment()
  let row = document.createElement("div")

  row.classList.add("automata-row")

  listCellStates.map(function(state) {
    return this.createCellElement(state)
  }.bind(this)).forEach(function(DOMElement) {
    row.appendChild(DOMElement)
  })

  frag.appendChild(row)
  return frag
};

CellularAutomata.prototype.run = function(DOMElement) {
  let frag = document.createDocumentFragment()
  let listCells = this.createFirstGeneration()
  let i = 1

  clearInterval(this.intervalID);
  this.gridStates.push(listCells);

  frag.appendChild(this.drawRow(frag, listCells))
  DOMElement.appendChild(frag);

  this.intervalID = setInterval(function() {
    let generationCells = this.step(i++)
    this.gridStates.push(generationCells)
    frag.appendChild(this.drawRow(frag, generationCells))
    DOMElement.appendChild(frag)
    if (i > this.generations) {
      clearInterval(this.intervalID);
    }
  }.bind(this), 50);
};

