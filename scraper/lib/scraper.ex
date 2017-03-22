defmodule Scraper do
  use HTTPoison.Base
  require Logger

  alias Scraper.Matcher

  @moduledoc """
  Exposes an interface for scraping the Genius API
  and adding lyrics to the lyrics bank
  """

  @doc """
  Makes a request to the MusixMatch API using
  the given method and params
  """
  def get(method, opts \\ %{}) do
    opts = Map.put opts, "apikey", config[:api_key]

    get!(method, [], params: opts).body
  end

  @doc """
  Accepting a map of params with `q_artist` and `q_track` fields,
  writes lyrics for the most relevant search result
  """
  def get_lucky(params) do
    params
    |> Matcher.lyrics
    |> extract_lyrics
    |> write
  end

  @doc """
  Appends lyrics line-by-line to lyrics file
  """
  def write(lyrics) do
    File.open config[:lyrics_file], ~w(write append utf8)a, &do_write(&1, lyrics)
  end

  defp do_write(device, lyrics) do
    lyrics
    |> String.split("\n")
    |> Stream.reject(&is_invalid/1)
    |> Enum.each(&IO.write(device, "#{&1}\n"))
  end

  defp extract_lyrics(%{"lyrics" => %{"lyrics_body" => lyrics}}), do: lyrics
  defp extract_lyrics([]), do: ""
  defp extract_lyrics(data) do
    Logger.error "Could not extract lyrics from: #{inspect data}"
  end

  defp is_invalid(line), do: Regex.match? ~r/\*{7}|(\d)/, line

  # Overwrite HTTPoison callbacks
  defp process_url(url),            do: config[:endpoint] <> url
  defp process_response_body(body)  do
    body
    |> Poison.decode!
    |> get_in(~w(message body))
  end

  defp config, do: Application.get_env :scraper, __MODULE__
end
