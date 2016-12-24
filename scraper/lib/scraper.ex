defmodule Scraper do
  use HTTPoison.Base

  @moduledoc """
  Exposes an interface for scraping the Genius API
  and adding lyrics to the JeezyAI lyrics bank
  """

  @lyrics_file "../lyrics/lyrics.txt"
  @file_modes ~w(binary append)a

  @doc """
  Makes a request to the MusixMatch API using
  the given method and params
  """
  def get(method, opts \\ %{}) do
    opts = Map.put opts, "apikey", config[:api_key]

    get! method, [], params: opts
  end

  @doc """
  Appends lyrics line-by-line to lyrics file
  """
  def write(lyrics) do
    File.open config[:lyrics_file], ~w(binary append)a, &do_write(&1, lyrics)
  end

  defp do_write(file, lyrics) do
    lyrics
    |> String.split("\n")
    |> Stream.reject(&is_invalid/1)
    |> Enum.each(&IO.write(file, "#{&1}\n"))
  end

  defp is_invalid(line), do: Regex.match? ~r/\*{7}|(\d)/, line

  defp process_url(url),            do: config[:endpoint] <> url
  defp process_response_body(body), do: Poison.decode! body

  defp config, do: Application.get_env :scraper, __MODULE__
end
