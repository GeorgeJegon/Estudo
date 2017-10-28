var gameBoard = document.getElementById('gameBoard'),
    gameBoardRows = Array.from(gameBoard.getElementsByClassName("row"));

// dropPiece(gameBoardRows, 0, "player-1");

var plays = 0, lockGame = false;

function getCurrentPlayer() {
  return !(plays%2) ? "player-1" : "player-2"
}

function clickDrop(gameBoardRows) {
  gameBoardRows.forEach(function(row, _) {
    Array.from(row.getElementsByClassName("cell")).forEach(function(cell, index) {
      cell.addEventListener("click", function(event) {
        if (!lockGame) { dropPiece(gameBoardRows, index); }
      });
    });
  });
};

function dropPiece(gameBoardRows, column) {
  lockGame = true;

  var columnCells = gameBoardRows.map(function(row) {
    return row.getElementsByClassName("cell")[column];
  }).filter(function(cell) {
    return !cell.classList.contains("filled");
  });

  animateDrop(columnCells);
}

function animateDrop(columnCells, index = 0) {
  var fn = animateDrop.bind(null, columnCells, index + 1);
  var currentPlayer = getCurrentPlayer();
  if (index == columnCells.length ) { plays++; lockGame = false; return; }
  if (index > 0) { columnCells[index - 1].classList.remove("filled", currentPlayer);  }

  columnCells[index].classList.add("filled", currentPlayer);

  setTimeout(fn, 110);
}

clickDrop(gameBoardRows);










