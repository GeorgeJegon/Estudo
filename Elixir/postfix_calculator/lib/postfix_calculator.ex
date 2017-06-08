defmodule PostfixCalculator do
  @moduledoc """
  Documentation for PostfixCalculator.
  """

  @doc """
  Hello world.

  ## Examples

      iex> PostfixCalculator.run([2, 3, "+"])
      5

      iex> PostfixCalculator.run([5, 2, 3, "+", "-"])
      0

      iex> PostfixCalculator.run([2, 3, 11, "+", 5, "-", "*"])
      18

      iex> PostfixCalculator.run([3, 11, 5, "+", "-"])
      -13

      iex> PostfixCalculator.run([10, 8, "-"])
      2

      iex> PostfixCalculator.run([10, 2, "/"])
      5

      iex> PostfixCalculator.run([2, 1, 12, 3, "/", "-", "+"])
      -1

      iex> PostfixCalculator.run([6, 3, "-", 2, "^", 11, "-"])
      -2
  """

  def run(expression), do: _run(expression)

  defp _run([head | []]), do: head
  defp _run(["^" | tail]), do: calc(&(round(:math.pow(&2, &1))), tail)
  defp _run(["/" | tail]), do: calc(&(div(&2, &1)), tail)
  defp _run(["*" | tail]), do: calc(&(&1 * &2), tail)
  defp _run(["-" | tail]), do: calc(&(&2 - &1), tail)
  defp _run(["+" | tail]), do: calc(&(&2 + &1), tail)
  defp _run([head | tail]), do: _run(tail |> List.insert_at(-1, head))

  defp calc(res, tail) when is_integer(res) do
    _run(tail |> Enum.drop(-2) |> List.insert_at(-1, res))
  end

  defp calc(f, tail) when is_function(f) do
    calc(tail |> Enum.take(-2) |> Enum.reduce(f), tail)
  end

  # http://www.meta-calculator.com/learning-lab/rpn-reverse-polish-notation-explained.php
end
