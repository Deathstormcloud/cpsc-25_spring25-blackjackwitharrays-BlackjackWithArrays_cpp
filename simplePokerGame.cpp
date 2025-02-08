/* 
Gongyu Yan
Alejandro Perez
Ryan Sowersby
Name
*/
import java.util.Random;
import java.util.Scanner;

public class BlackJack {

    private static final String[] SUITS = {"Hearts", "Diamonds", "Clubs", "Spades"};
    private static final String[] RANKS = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    private static final int[] DECK = new int[52];
    private static int currentCardIndex = 0;
    private static int wins = 0;
    private static int losses = 0;
    private static int ties = 0;
    private static boolean doubled = false; // Gongyu Yan, added the doubling mechanic

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean playAgain = true;

        while (playAgain) {
            initializeDeck();
            shuffleDeck();

            int playerTotal = dealInitialPlayerCards();
            int dealerTotal = dealInitialDealerCards();

            playerTotal = playerTurn(scanner, playerTotal);
            if (playerTotal > 21) {
                System.out.println("You busted! Dealer wins.");
                losses++;  // Track loss
            } else {
                dealerTotal = dealerTurn(dealerTotal);
                determineWinner(playerTotal, dealerTotal);
            }

            displayStats();  // Display stats after the game

            // Ask if the player wants to play another round
            System.out.println("Do you want to play another round? (y/n)"); 
            String response = scanner.nextLine().toLowerCase();
            if (!response.equals("y")) {
                playAgain = false;
            }
        }

        System.out.println("Thanks for playing! Final stats:");
        displayStats();  // Final stats display
        scanner.close();
    }

    private static void initializeDeck() {
        for (int i = 0; i < DECK.length; i++) {
            DECK[i] = i;
        }
        currentCardIndex = 0;  // Reset the current card index for each round
    }

    private static void shuffleDeck() {
        Random random = new Random();
        for (int i = 0; i < DECK.length; i++) {
            int index = random.nextInt(DECK.length);
            int temp = DECK[i];
            DECK[i] = DECK[index];
            DECK[index] = temp;
        }
    }

    private static int dealInitialPlayerCards() {
        int card1 = dealCard();
        int card2 = dealCard();
        System.out.println("Your cards: " + RANKS[card1] + " of " + SUITS[card1 / 13] + " and " + RANKS[card2] + " of " + SUITS[card2 / 13]);
        return cardValue(card1) + cardValue(card2);
    }

    private static int dealInitialDealerCards() {
        int card1 = dealCard();
        System.out.println("Dealer's card: " + RANKS[card1] + " of " + SUITS[card1 / 13]);
        return cardValue(card1);
    }

    private static int playerTurn(Scanner scanner, int playerTotal) {
        while (true) {
            System.out.println("Your total is " + playerTotal + ". Do you want to hit, stand or double?");
            String action = scanner.nextLine().toLowerCase();
            if (action.equals("hit")) {
                int newCard = dealCard();
                playerTotal += cardValue(newCard);
                System.out.println("You drew a " + RANKS[newCard] + " of " + SUITS[newCard / 13]);
                if (playerTotal > 21) {
                    break;
                }
            } 
            else if (action.equals("stand")) {
                break;
            }
              else if (action.equals("double")) { // Gongyu Yan, added the doubling mechanic
                doubled = true;
                int newCard = dealCard();
                playerTotal += cardValue(newCard);
                System.out.println("You drew a " + RANKS[newCard] + " of " + SUITS[newCard / 13]);
                break;
            } else {
                System.out.println("Invalid action. Please type 'hit' or 'stand'.");
            }
        }
        return playerTotal;
    }

    private static int dealerTurn(int dealerTotal) {
        while (dealerTotal < 17) {
            int newCard = dealCard();
            dealerTotal += cardValue(newCard);
        }
        System.out.println("Dealer's total is " + dealerTotal);
        return dealerTotal;
    }

            private static void determineWinner(int playerTotal, int dealerTotal) { // Gongyu Yan, added the doubling mechanic
                if (dealerTotal > 21 || playerTotal > dealerTotal) {
                    if (doubled) {
                        System.out.println("You win doubled!");
                        wins += 2;  // Award 2 points if doubled
                    } else {
                        System.out.println("You win!");
                        wins++;  // Award 1 point if not doubled
                    }
        } else if (dealerTotal == playerTotal) {
            System.out.println("It's a tie!");
            ties++;  // Track tie
        } else {
            System.out.println("Dealer wins!");
            losses++;  // Track loss
        }
    }

    private static int dealCard() {
        return DECK[currentCardIndex++] % 13;
    }

    private static int cardValue(int card) {
        return card < 9 ? card + 2 : 10;
    }

    private static void displayStats() { // Alejandro P, Ryan S, added the stats display
        System.out.println("----------------------------------");
        System.out.println("Current Stats:");
        System.out.println("Wins: " + wins);
        System.out.println("Losses: " + losses);
        System.out.println("Ties: " + ties);
        System.out.println("----------------------------------");
    }
}
