# this is a comment
# [p] = print
# [c {choices}] = choice;
#   Example: [c {a:Label 1;b:Label 2;c:Label 3}]
# [a] = choice type
# [q quotee] = quote;
#   Output: "Quotee": q

[p]  ________            ______                      __         
[p] /_  __/ /_  ___     /_  __/________ __   _____  / /__  _____
[p]  / / / __ \/ _ \     / / / ___/ __ `/ | / / _ \/ / _ \/ ___/
[p] / / / / / /  __/    / / / /  / /_/ /| |/ /  __/ /  __/ /    
[p]/_/ /_/ /_/\___/    /_/ /_/   \__,_/ |___/\___/_/\___/_/     
[p]                      A Short Story by Maarten Wolfsen
[p]---- Main Menu -------------------------------------
[c {a:Start Game;b:Quit to Desktop}]
    [a]
        [q Bartender]Hello weary Traveler. You have been on quite the Journey, what is your name?
        [f setName]
        [q Bartender]So Traveler... I have never seen you before...
        [q Bartender]Where are you from?
        [f setLocation]
        [q Bartender]Ah... From afar I see...
        [q Bartender]Make yourself at home, ask me if you need anything.
        [c {a:Grab a drink and sit at the bar.;b:Grab a drink and sit at a empty table.;c:Grab a drink and sit at a table beside someone.}]
            [a]
                [p]You order a drink and go sit at the bar.
                [p]After a short while, a stranger sits right next to you and orders a beer.
                [p]You notice his hand is torn open and bleeding.
                [q Bartender]How are you going to pay for that beer, stranger?
                [p]It seems that the stranger does not have enough money to pay for the beer.
                [c {a:Pay for his beer.;b:Don't pay for his beer.}]
                    [a]
                        [q Stranger]Thank you Traveler...
                        [end]
                    [b]
                        [end]
                
            [b]
                [end]
            [c]
                [end]
    [b]
        [end]