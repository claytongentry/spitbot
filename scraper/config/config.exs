use Mix.Config

config :scraper, Scraper,
  endpoint: "http://api.musixmatch.com/ws/1.1"

import_config "./secrets.exs"
