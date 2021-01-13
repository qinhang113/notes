function get(url, success, failure)
{
    var xhr = new XMLHttpRequest;
    xhr.open("GET", url);
    xhr.onreadystatechange = function() {
        handleResponse(xhr, success, failure);
    }
    xhr.send();
}
function handleResponse(xhr, success, failure){
    if (xhr.readyState === XMLHttpRequest.DONE) {
        if (xhr.status ===  200){
            if (success !== null && success !==undefined)
            {
                var result = xhr.responseText;
                try{
                    success(result, JSON.parse(result));
                }catch(e){
                    success(result, {});
                }
            }
        }
        else{
            console.log(xhr.status)
            if (failure !== null && failure !== undefined)
                failure(xhr.responseText, xhr.status);
        }
    }
}


