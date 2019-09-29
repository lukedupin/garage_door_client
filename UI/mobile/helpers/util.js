.pragma library

function capitalize( string )
{
    return string.charAt(0).toUpperCase() + string.slice(1)
}

function roundNumber(number, digits)
{
    var multiple = Math.pow(10, digits);
    return Math.round(number * multiple) / multiple;
}

function epochToDate(sec)
{
    var d = new Date(0)
    d.setUTCSeconds(sec)

    return (d.getMonth() + 1) +"/"+ d.getDate() +"/"+ d.getFullYear().toString().slice(-2)
}

function epochToTime(sec, short)
{
    var d = new Date(0)
    d.setUTCSeconds(sec)

    if ( short === true)
    {
        var min = d.getMinutes()
        return d.getHours() +":"+ (((min < 10)? "0": "") + min)
    }
    else
        return d.toLocaleTimeString()
}

function epochToDateTime(sec)
{
    return epochToDate(sec) +" "+ epochToTime(sec, true)
}

function lpad(str, count, char)
{
    if ( char === undefined || char === null)
        char = ' '
    while ( str.length < count )
        str = char + str

    return str
}

function rpad(str, count, char)
{
    if ( char === undefined || char === null)
        char = ' '
    while ( str.length < count )
        str = str + char

    return str
}

function formatTime(sec, show_label)
{
    if ( show_label === undefined || show_label === null )
        show_label = true
    if ( show_label === false )
    {
        var min = Math.round(sec / 60)
        if ( min < 60 )
            return min

        return Math.floor(min / 60) +":"+ lpad( (min % 60).toString(), 2, '0' )
    }

    var value = sec
    var seconds = value % 60
    value /= 60
    value = (value > 1) ? Math.round(value) : 0
    var minutes = value % 60
    value /= 60
    value = (value > 1) ? Math.floor(value) : 0
    var hours = value
    if (hours > 0) value = hours + "h:"+ lpad( minutes.toString(), 2, '0' ) + "m"
    else value = minutes + " min"
    return value
}

function formatDistance(meters)
{
    var dist = Math.round(meters)
    if (dist > 1000 )
    {
        if (dist > 100000)
            dist = Math.round(dist / 1000) // No decimial
        else
            dist = (dist / 100).toFixed(1)

        return dist + " km"
    }

    return Math.round(dist) + " m"
}
