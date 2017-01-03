use Mix.Config

config :scraper, Scraper,
  endpoint: "http://api.musixmatch.com/ws/1.1",
  lyrics_file: "../lyrics/lyrics.txt"

import_config "./secrets.exs"
