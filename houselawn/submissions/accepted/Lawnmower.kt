// author Torstein Stromme

data class Lawnmower(val name: String, val price: Int, val id: Int)

fun main(args: Array<String>) {
    // Let l be square footage to cut, let m be number of possible lawnmowers
    val (l, m) = readLine()!!.split(' ').map(String::toInt)

    // Fill array with lawnmowers
    val mowers: MutableList<Lawnmower> = ArrayList<Lawnmower>()
    var bestPrice = 1000*1000

    for (i in 0 until m) {
        val (name, price, cutcap, cuttime, recharge) = readLine()!!.split(',')
        if (price.toInt() <= bestPrice && canCut(l, cutcap.toInt(), cuttime.toInt(), recharge.toInt())) {
            if (price.toInt() < bestPrice) {
                mowers.clear()
                bestPrice = price.toInt()
            }
            mowers.add(Lawnmower(name, price.toInt(), i))
        }
    }

    if (mowers.size == 0)
        println("no such mower")
    else {
//        mowers.sortWith(compareBy({it.price}, {it.id}))
        for (mower in mowers) {
            println(mower.name)
        }

    }
}

fun canCut(lawn: Int, cutcap: Int, cuttime: Int, recharge: Int): Boolean {
    val percharge = cuttime * cutcap
    val charges = 24.0 * 7.0 * 60.0 / (recharge + cuttime)
    // System.err.printf("per charge: %d, charges: %f, cutaweek: %f\n", percharge, charges, charges*percharge)
    return charges * percharge >= lawn
}
