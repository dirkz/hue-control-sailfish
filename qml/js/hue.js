.pragma library

.import "underscore/underscore.js" as U

var _ = U.init()

function encloseTag(tag, s) {
    return "<" + tag + ">" + s + "</" + tag + ">";
}

function lineBreak() {
    return "<br>"
}

function errors(json) {
    return _.filter(_.pluck(json, 'error'), _.identity)
}

function errorDescriptions(json) {
    return _.pluck(errors(json), 'description').join("\n")
}

function lightsList(json) {
    var buildLight = function(key) {
        var obj = json[key]
        obj.lightId = key
        return obj
    }

    var keys = _.sortBy(_.keys(json), parseInt)
    var lights = _.map(keys, buildLight)
    return lights
}

function flat1(objs) {
    var r = _.reduce(objs, function(acc, ary) {
        return acc.concat(ary)
    }, [])
    return r
}

function extractSingleStateValue(json, stateUrl) {
    var match = new RegExp("^" + stateUrl + "$")
    var objs = _.pluck(json, 'success')
    var pairs = _.map(objs, _.pairs)
    var props = flat1(pairs)
    if (_.isArray(props) && props.length > 0) {
        if (match.test(props[0][0])) {
            return props[0][1]
        } else {
            return undefined
        }
    } else {
        return undefined
    }
}

function checkErrors(json, messageLabel) {
    var errs = errors(json)
    if (errs.length > 0) {
        messageLabel.text = errorDescriptions(json)
        return true
    } else {
        return false
    }
}
