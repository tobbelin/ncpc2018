import scala.io.StdIn._

// Some papers on 1-factorization on complete multipartite graphs
// https://pdfs.semanticscholar.org/163f/34ff7f7591974eba64df6e7c8ada045d52cb.pdf
// https://pdfs.semanticscholar.org/9d06/210bb12aaafc4d22bcc723f9258cfb658ae5.pdf

object Jimmy extends App {
  // n participants in every team, m teams
  val Array(n, m) = readLine.split(" ").map(_.toInt)

  // Returns a List[List[(Int, Int)]] with pairings for all rounds (n elements)
  def tournamentOdd(n:Int) = List.range(0, n).map(
    round => List.range(0, n/2).map(no => ((no + round) % n, (n - 2 - no + round ) % n)))

  // Returns a List[Int] with the player who has a bye for each round
  def tournamentOddByes(n:Int) = List.range(0, n).map(round => (n - 1 + round) % n)

  def tournamentEven(n:Int) = tournamentOdd(n-1).zip(tournamentOddByes(n-1))
    .map{case (round, bye) => round :+ (bye,n-1)}

  def tournament(n:Int) = if (n%2==0) tournamentEven(n) else tournamentOdd(n)

  val p1 = tournament(n)
    .flatMap(pairings => List.range(1, m)
      .map(round => pairings
        .flatMap { case (home, away) => List.range(0, m)
          .map(tbl => (tbl, home, (tbl + round) % m, away)) }))

  val pairings = if (n % 2 == 0) {
    p1 ::: tournament(m)
      .map(round => List.range(0, n)
        .flatMap(no => round
          .map { case (home, away) => (home, no, away, no) } ))
  } else {
    val p2 = tournamentOddByes(n)
      .flatMap(bye => tournament(m)
        .map(_.map { case (home,away) => (home, bye, away, bye) }))

    val (p3, p4) = if (m % 2 == 1) {
      val (left, right) = p2.zipWithIndex.partition{ case (_, y) => y % m > 0 }
      (left.map(_._1), right.flatMap(_._1))
    } else {
      (p2, List())
    }

    p1.zip(p3).map { case (q1, q2) => q1 ++ q2 } :+ p4
  }

  pairings.foreach(round => println(round.map{
    case (ht, hn, at, an) => "%c%d-%c%d".format(ht + 'A', hn + 1, at + 'A', an + 1) }.mkString(" ")))

}
