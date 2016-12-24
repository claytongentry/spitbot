defmodule Scraper do
  use HTTPoison.Base

  @moduledoc """
  Exposes an interface for scraping the Genius API
  and adding lyrics to the JeezyAI lyrics bank
  """

  def get(method, opts \\ %{}) do
    opts = Map.put opts, "apikey", config[:api_key]

    get! method, [], params: opts
  end

  defp process_url(url),            do: config[:endpoint] <> url
  defp process_response_body(body), do: Poison.decode! body

  defp config, do: Application.get_env :scraper, __MODULE__
end
