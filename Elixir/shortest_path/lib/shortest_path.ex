defmodule ShortestPath do
  @moduledoc """
  Documentation for ShortestPath.
  """

  @doc """
  Hello world.

  ## Examples

      iex> ShortestPath.resolve([{50, 10, 30}, {5, 90, 20}, {40, 2, 25}, {10, 8, 0}])
      [{:b,10},{:x,30},{:a,5},{:x,20},{:b,2},{:b,8}]

      iex> ShortestPath.resolve([{5, 1, 3}, {10, 15, 0}])
      [{:b,1},{:x,3},{:a,10}]


  """
  def resolve(paths) do
    {a, b} = List.foldl(paths, {{0, []}, {0, []}}, &_resolve/2)
    {_, path} = cond do
      hd(elem(a, 1)) != {:x, 0}  -> a
      hd(elem(b, 1)) != {:x, 0}  -> b
    end

    Enum.reverse(path)
  end

  defp _resolve({a, b, x}, {{distA, pathA}, {distB, pathB}}) do
    oa  = {distA + a, [{:a, a} | pathA]}
    oa1 = {distB + b + x, [{:x, x}, {:b, b} | pathB]}
    ob  = {distA + a + x, [{:x, x}, {:a, a} | pathA]}
    ob1 = {distB + b, [{:b, b} | pathB]}

    { :erlang.min(oa, oa1), :erlang.min(ob, ob1) }
  end
end
