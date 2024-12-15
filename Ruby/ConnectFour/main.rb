$LOAD_PATH.unshift "./lib"

require "game"

game = Game.new

begin
  puts "---------- Vez do Jogador #{game.current_player}! ----------"
  puts "---------- Escolha uma coluna para jogar! ----------"

  column_selected  = gets.chomp.to_i

  game.drop(column_selected)

end while(!game.finished?)
