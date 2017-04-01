defmodule Mix.Tasks.Scraper.Write do
  use Mix.Task
  require Logger

  def run([ artist | tracks ]) do
    Mix.Task.run "app.start"

    write artist, tracks
  end

  defp write(_artist, []),               do: []
  defp write(artist, [ track | tracks ]) do
    Logger.info "Writing #{track} by #{artist} to the bank..."

    Scraper.get_lucky %{
      "q_artist" => artist,
      "q_track"  => track
    }

    write artist, tracks
  end
end
