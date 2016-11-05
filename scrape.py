import urllib
import urllib2

def scrape():
    token   = secrets["GENIUS_TOKEN"]
    data    = urllib.urlencode({})
    headers = {'Authorization': 'Bearer ' + token}
    req     = urllib2.Request("https://api.genius.com/annotations/10225840", data, headers)

    urllib2.urlopen(req)

def main():
    scrape()

    print "Done."

if __name__ == "__main__":
    print "Scraping Genius..."
    main()
